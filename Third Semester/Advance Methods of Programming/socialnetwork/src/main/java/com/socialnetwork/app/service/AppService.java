package com.socialnetwork.app.service;

import com.socialnetwork.app.domain.Friendship;
import com.socialnetwork.app.domain.Message;
import com.socialnetwork.app.domain.User;

import com.socialnetwork.app.domain.validation.*;
import com.socialnetwork.app.exceptions.NetworkException;
import com.socialnetwork.app.exceptions.RepoException;
import com.socialnetwork.app.exceptions.ValidationException;
import com.socialnetwork.app.repository.FriendshipRepo;
import com.socialnetwork.app.repository.MessageRepo;
import com.socialnetwork.app.repository.Network;
import com.socialnetwork.app.repository.UserRepo;
import com.socialnetwork.app.utils.Observer.Observable;
import com.socialnetwork.app.utils.Observer.Observer;

import java.util.*;
import java.util.stream.Collectors;

public class AppService implements Service, Observable {
    private final UserRepo repository_user;
    private final Validator<User> validator;
    private final Validator<Friendship> validator_fr;
    private final FriendshipRepo repository_friendship;

    private MessageRepo repository_message;

    private int lastIdUser;
    private int lastIdFriendship;
    private int lastIdMessage;


    public AppService(UserRepo repository_user, FriendshipRepo repository_friendship, MessageRepo repository_message,Validator<User> validator, Validator<Friendship> validator2) {
        this.repository_user = repository_user;
        this.validator = validator;
        this.validator_fr = validator2;
        this.repository_friendship = repository_friendship;
        this.repository_message=repository_message;
        lastIdUser = this.repository_user.getLastID();
        lastIdFriendship = this.repository_friendship.getLastID();
        lastIdMessage=this.repository_message.getLastID();
        observers = new ArrayList<>();
    }

    /**
     * Adds a friendship between the users with given ids
     *
     * @param id1 int
     * @param id2 int
     * @throws NetworkException if there already exists a friendship
     * @throws RepoException    if the users do not exist
     */
    @Override
    public void addFriendship(int id1, int id2) throws RepoException, ValidationException {

        User u1 = repository_user.findElement(id1);
        User u2 = repository_user.findElement(id2);
        Friendship f1 = new Friendship(u1, u2);
        validator_fr.validate(f1);
        Friendship friendship = existPendingFriendship(f1);
        if (friendship == null) {
            f1.setId(lastIdFriendship + 1);
            lastIdFriendship += 2;
            repository_friendship.add(f1);
        } else repository_friendship.acceptFriendshipInDB(friendship);
        notifyObserevers();


    }

    public Friendship existPendingFriendship(Friendship f1) {
        List<Friendship> friendships = repository_friendship.getAll();
        Optional<Friendship> optionalFriendship = friendships.stream()
                .filter(friendship -> Objects.equals(friendship.getUser1().getId(), f1.getUser2().getId()) && friendship.getUser2().getId() == f1.getUser1().getId())
                .findFirst();

        boolean isPresent = optionalFriendship.isPresent();
        if (isPresent)
            return optionalFriendship.get();
        else return null;
    }

    /**
     * Removes a friendship from the system
     *
     * @param id1 int
     * @param id2 int
     * @throws if            friendship does not exist
     * @throws RepoException if the users do not exist
     */
    @Override
    public void removeFriendship(int id1, int id2) throws Exception {

        User u1 = repository_user.findElement(id1);
        User u2 = repository_user.findElement(id2);
        Friendship f1 = new Friendship(u1, u2);
        // Friendship f2=new Friendship(u2,u1);
        validator_fr.validate(f1);
        // validator_fr.validate(f2);

        repository_friendship.remove(f1);
        // repository_friendship.remove(f2);

        notifyObserevers();
    }

    /**
     * Get friends of a user with given id
     *
     * @param id int
     * @return Map<User, String>
     */
    @Override
    public HashMap<User, String> getFriends(int id) {

        HashMap<User, String> users = new HashMap<>();
        List<Friendship> friendships = repository_friendship.getAll();
        for (Friendship friendship : friendships)
            if (friendship.getStatus().equals("ACCEPTED") || friendship.getStatus().equals("PENDING")) {
                if (friendship.getUser1().getId() == id)
                    users.put(friendship.getUser2(), friendship.getFriendsFrom());
                else if (friendship.getUser2().getId() == id)
                    users.put(friendship.getUser1(), friendship.getFriendsFrom());
            }

        return users;
    }

    /**
     * Retruns list of the pending friendships of user with given id
     *
     * @param id - int
     * @return List<User>
     */
    @Override
    public List<User> getFriendRequests(int id) {
        List<User> friendRequests = new ArrayList<>();
        for (Friendship friendship : repository_friendship.getAll())
            if (friendship.getStatus().equals("PENDING")) {
                if (friendship.getUser2().getId() == id)
                    friendRequests.add(friendship.getUser1());
            }
        return friendRequests;
    }

    /**
     * @return a network based on the current friendships
     */
    private Network createNetwork() {
        return new Network(repository_friendship.getAll());
    }

    @Override
    public int numberOfCommunities() {
        Network network = createNetwork();
        return network.getNumberOfCommunities();
    }

    /**
     * @return list with the users from the most sociable community
     */
    @Override
    public List<User> mostSociableCommunity() {
        Network network = createNetwork();
        var lista = network.mostSociableCommunity();
        List<User> userList = new ArrayList<>();
        if (lista != null) {
            for (int id : lista)
                try {
                    userList.add(repository_user.findElement(id));
                } catch (RepoException ignored) {
                }
        }
        return userList;
    }


    /**
     * Removes a user by id
     *
     * @param id int
     * @throws Exception if the user with given id does not exist
     */
    @Override
    public void remove(int id) throws Exception {
        User user = repository_user.findElement(id);

        repository_friendship.removeAllFriendshipsByUser(user);
        repository_user.remove(user);
        notifyObserevers();
    }

    /**
     * Adds a user to the system with given information
     *
     * @param firstName String
     * @param lastName  String
     * @param email     String
     * @throws Exception if the given paramaters are not valid
     */
    @Override
    public void add(String firstName, String lastName, String email) throws Exception {
        int id = lastIdUser + 1;
        lastIdUser++;
        User user = new User(lastName, firstName, email);
        user.setId(id);
        validator.validate(user);
        repository_user.add(user);
        notifyObserevers();

    }

    /**
     * Finds a user by given id
     * @param id Integer
     * @return User
     */
    @Override
    public User findUserById(int id) {
        Optional<User> optionalFriend = repository_user.getAll().stream()
                .filter(user -> user.getId() == id)
                .findFirst();
        return optionalFriend.orElse(null);
    }

    /**
     * Finds a user by given email
     * @param email
     * @return
     * @throws RepoException
     */
    @Override
    public User findUserByEmail(String email) throws RepoException{
        return repository_user.findUserByEmail(email);
    }

    /**
     * Updates a user that has the given id with the given attributes
     *
     * @param idToChange int
     * @param firstName  String
     * @param lastName   String
     * @param email      String
     * @throws RepoException       if no user is found
     * @throws ValidationException if the given attributes are invalid
     */
    @Override
    public void update(int idToChange, String firstName, String lastName, String email) throws RepoException, ValidationException {
        User u1 = new User(firstName, lastName, email);
        u1.setId(idToChange);
        validator.validate(u1);
        repository_user.update(u1);
        notifyObserevers();
    }

    /**
     * @return all friendships
     */
    @Override
    public List<Friendship> getAllFriendships() {
        return repository_friendship.getAll();
    }

    /**
     * @return number of friendships
     */
    @Override
    public int sizeFriendships() {
        return repository_friendship.size();
    }

    /**
     * @return number of users
     */
    @Override
    public int sizeUsers() {
        return repository_user.size();
    }

    /**
     * @return a list with all the users
     */
    @Override
    public List<User> getAllUsers() {
        return repository_user.getAll();
    }

    List<Observer> observers;

    /**
     * Adds an observer to the observer list
     * @param observer Observer
     */
    @Override
    public void addObserver(Observer observer) {
        observers.add(observer);
    }

    /**
     * Removes an observer from the observer list
     * @param observer Observer
     */
    @Override
    public void removeObserver(Observer observer) {
        observers.remove(observer);
    }

    /**
     * Executes update method of all observers
     */
    @Override
    public void notifyObserevers() {
        observers.stream().forEach(observer -> observer.update());
    }


    /**
     * Get all the messages for the given user
     * @param id_user Integer
     * @return List < Message >
     */
    @Override
    public List<Message> getMessagesForUser(int id_user){
        List<Message> messages=repository_message.getAll().stream()
                .filter(message -> message.getReceiver().getId()==id_user || message.getSender().getId()==id_user)
                .collect(Collectors.toList());

        Comparator<Message> comparator = new Comparator<Message>() {
            @Override
            public int compare(Message o1, Message o2) {
                return o1.getId()- o2.getId();
            }
        };
        messages.sort(comparator);

        return messages;
    }

    /**
     * Adds a message to the message database
     * @param id_sender - Integer
     * @param id_receiver - Integer
     * @param message - String
     * @throws RepoException
     */
    @Override
    public void addMessage(int id_sender, int id_receiver, String message) throws RepoException {

        User sender=repository_user.findElement(id_sender);
        User receiver=repository_user.findElement(id_receiver);
        Message newMessage=new Message(sender,receiver,message);
        newMessage.setId(lastIdMessage+1);
        lastIdMessage++;
        repository_message.add(newMessage);
        notifyObserevers();
    }

    /**
     * Gets all the messages between the users who have the given id
     * @param id_user1 - Integer
     * @param id_user2 - Integer
     * @return List < Message >
     */
    @Override
    public List<Message> getMessagesBetweenUsers(int id_user1, int id_user2) {
        return getMessagesForUser(id_user1).stream()
                .filter(message -> message.getSender().getId() == id_user2 || message.getReceiver().getId()==id_user2)
                .collect(Collectors.toList());
    }
}