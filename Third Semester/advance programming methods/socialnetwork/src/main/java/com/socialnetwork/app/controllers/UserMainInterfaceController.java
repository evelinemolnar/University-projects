package com.socialnetwork.app.controllers;

import com.socialnetwork.app.Main;
import com.socialnetwork.app.domain.*;
import com.socialnetwork.app.exceptions.RepoException;
import com.socialnetwork.app.service.AppService;
import com.socialnetwork.app.utils.Observer.Observer;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;


import java.util.*;
import java.util.stream.Collectors;

public class UserMainInterfaceController implements Observer {

    private final ObservableList<User> usersList = FXCollections.observableArrayList();
    private final ObservableList<UserDTOFriend> friendList = FXCollections.observableArrayList();

    private final ObservableList<MessageDTO> messagesList = FXCollections.observableArrayList();

    private final ObservableList<User> friendRequestsList = FXCollections.observableArrayList();
    private User loggedUser = null;

    @FXML
    private TableColumn<MessageDTO, String> messageToUserColumn;

    @FXML
    private TableColumn<MessageDTO, String> messageFromUserColumn;
    @FXML
    public AnchorPane friendRequestsPane;
    @FXML
    public Button acceptFriendButton;
    @FXML
    public Button rejectFriendButton;

    @FXML
    public Button removeFriendButton;

    @FXML
    public Button sendMessageButton;

    @FXML
    public Button addFriendshipButton;
    @FXML
    public TextField searchUserTextField;

    @FXML
    public Label connectedUserLabel;
    @FXML
    public Label emailUserLabel;
    @FXML
    private TextField messageTextField;

    @FXML
    private VBox chatPane;

    @FXML
    public TableView<UserDTOFriend> friendsTableView;
    @FXML
    public ListView<User> friendRequestsListView;
    @FXML
    public TableView<User> usersTable;
    @FXML
    private TableView<MessageDTO> chatTable;

    @FXML
    public TableColumn<UserDTOFriend, String> friendNameColumn;
    @FXML
    public TableColumn<UserDTOFriend, String> friendsSinceColumn;
    @FXML
    public TableColumn<User, String> firstNameColumn;
    @FXML
    public TableColumn<User, String> lastNameColumn;
    @FXML
    public TableColumn<User, String> emailColumn;

    @FXML
    public Button refreshButton;

    @FXML
    public Button send;

    @FXML
    public Button backButton;

    @FXML
    public Button removeAccountButton;

    @FXML
    public Button logoutButton;

    @FXML
    public ImageView profileImageView;

    @FXML
    public ImageView profilImageView;
    private AppService service;



    @FXML
    public void onLogoutButtonAction(){
        FXMLLoader loader = new FXMLLoader(Main.class.getResource("LoginInterfaceView.fxml"));
        Scene scene;
        try{
            scene = new Scene(loader.load(), 290, 400);
        }
        catch (Exception ex){
            ex.printStackTrace();
            return;
        }
        LoginInterfaceController controller=loader.getController();
        controller.setService(service);
        Stage currentStage= (Stage) removeAccountButton.getScene().getWindow();

        Stage newStage = new Stage();
        newStage.setScene(scene);
        newStage.setResizable(false);
        newStage.setTitle("SocialNetwork");
        currentStage.close();
        newStage.show();
        profilImageView.setImage(new Image("https://telanganatoday.com/wp-content/uploads/2021/10/Tips-to-keep-your-Instagram-account-safe.jpg"));
    }
    @FXML
    public void onRemoveAccountAction(){
        try {
            service.remove(loggedUser.getId());

            FXMLLoader loader = new FXMLLoader(Main.class.getResource("LoginInterfaceView.fxml"));
            Scene scene;
            try{
                scene = new Scene(loader.load(), 290, 400);
            }
            catch (Exception ex){
                ex.printStackTrace();
                return;
            }
            LoginInterfaceController controller=loader.getController();
            controller.setService(service);
            Stage currentStage= (Stage) removeAccountButton.getScene().getWindow();

            Stage newStage = new Stage();
            newStage.setScene(scene);
            newStage.setResizable(false);
            currentStage.close();
            newStage.show();
        }
        catch(Exception ex){
            ex.printStackTrace();
            Alert alert=new Alert(Alert.AlertType.ERROR,"No action finished!",ButtonType.OK);
            alert.show();
        }
    }
    public void setService(AppService service, User user) {


        boolean visibleFriendrequestsPane = true;
        friendRequestsPane.setVisible(visibleFriendrequestsPane);
        chatPane.setVisible(false);
        this.service = service;
        this.service.addObserver(this);
        this.loggedUser = user;

        connectedUserLabel.setText(loggedUser.getFirstName() + " " + loggedUser.getLastName());
        emailUserLabel.setText(loggedUser.getEmail());
        profileImageView.setImage(new Image("https://icones.pro/wp-content/uploads/2021/02/instagram-logo-icone4.png"));
        initLists();
    }

    private void initLists() {
        HashMap<User, String> friendsOfUser = service.getFriends(loggedUser.getId());

        List<UserDTOFriend> friendsTemp = new ArrayList<>();

        for (User user : friendsOfUser.keySet()) {
            UserDTOFriend friend = new UserDTOFriend(user, friendsOfUser.get(user));
            friendsTemp.add(friend);
        }
        List<User> friendReqOfUsers = service.getFriendRequests(loggedUser.getId());
        List<User> friendReqTemp = new ArrayList<>(friendReqOfUsers);
        friendList.setAll(friendsTemp);
        friendRequestsList.setAll(friendReqTemp);

        List<User> allUsers = service.getAllUsers();
        List<User> allUsersTempList = allUsers.stream()
                .filter(user -> !Objects.equals(user.getId(), loggedUser.getId()))
                .collect(Collectors.toList());

        usersList.setAll(allUsersTempList);
    }

    @FXML
    public void onAcceptButton() {

        try {
            int id = friendRequestsListView.getSelectionModel().getSelectedItem().getId();
            service.addFriendship(loggedUser.getId(), id);
        } catch (NullPointerException npe) {
            Alert alert = new Alert(Alert.AlertType.WARNING, "No user selected!", ButtonType.OK);
            alert.show();
        } catch (Exception ex) {
            Alert alert = new Alert(Alert.AlertType.ERROR, ex.getMessage(), ButtonType.OK);
            alert.show();
        }
    }


    @FXML
    public void onRejectFriendrequestButton() {
        try {
            int userID = friendRequestsListView.getSelectionModel().getSelectedItem().getId();
            service.removeFriendship(loggedUser.getId(), userID);
        } catch (NullPointerException npe) {
            Alert alert = new Alert(Alert.AlertType.WARNING, "No user selected!", ButtonType.OK);
            alert.show();
        } catch (Exception ex) {
            Alert alert = new Alert(Alert.AlertType.ERROR, ex.getMessage(), ButtonType.OK);
            alert.show();
        }
    }

    @FXML
    public void onAddFriendButton() {
        try {
            User userToAskFriendship = usersTable.getSelectionModel().getSelectedItem();
            service.addFriendship(loggedUser.getId(), userToAskFriendship.getId());
            Alert alert = new Alert(Alert.AlertType.INFORMATION, "Sent friendrequest", ButtonType.OK);
            alert.show();

        } catch (NullPointerException npe) {
            Alert alert = new Alert(Alert.AlertType.WARNING, "No user selected!", ButtonType.OK);
            alert.show();
        } catch (Exception ex) {
            Alert alert = new Alert(Alert.AlertType.ERROR, ex.getMessage(), ButtonType.OK);
            alert.show();
        }

    }

    @FXML
    public void onRemoveFriendButton() {

        try {
            int friendID = friendsTableView.getSelectionModel().getSelectedItem().getUID();
            service.removeFriendship(friendID, loggedUser.getId());
        } catch (NullPointerException npe) {
            Alert alert = new Alert(Alert.AlertType.WARNING, "No friend selected!", ButtonType.OK);
            alert.show();
        } catch (Exception ex) {
            ex.printStackTrace();
            Alert alert = new Alert(Alert.AlertType.ERROR, ex.getMessage(), ButtonType.OK);
            alert.show();
        }
    }

    @FXML
    public void onSearchUserTextField() {
        List<User> users = service.getAllUsers();
        List<User> usersTemp = new ArrayList<>();
        for (User user : users) {
            String name = user.getFirstName() + " " + user.getLastName();
            if (name.startsWith(searchUserTextField.getText()) && !Objects.equals(user.getId(), loggedUser.getId()))
                usersTemp.add(user);
        }
        usersList.setAll(usersTemp);
        usersTable.setItems(usersList);
    }

    @FXML
    public void initialize() {
        friendNameColumn.setCellValueFactory(new PropertyValueFactory<>("name_user"));
        friendsSinceColumn.setCellValueFactory(new PropertyValueFactory<>("friendsSince"));

        messageToUserColumn.setCellValueFactory(new PropertyValueFactory<>("toMessage"));
        messageFromUserColumn.setCellValueFactory(new PropertyValueFactory<>("fromMessage"));


        firstNameColumn.setCellValueFactory(new PropertyValueFactory<>("firstName"));
        lastNameColumn.setCellValueFactory(new PropertyValueFactory<>("lastName"));
        emailColumn.setCellValueFactory(new PropertyValueFactory<>("email"));
        usersTable.setItems(usersList);

        friendRequestsListView.setItems(friendRequestsList);
        friendsTableView.setItems(friendList);

        chatTable.setItems(messagesList);


        searchUserTextField.textProperty().addListener(o -> onSearchUserTextField());
    }

    @Override
    public void update() {
        initLists();
    }

    @FXML
    public void onUserFromUserMessageListClick() {
        //make visibile pane
        chatPane.setVisible(true);
        int fromUserID = friendsTableView.getSelectionModel().getSelectedItem().getUID();
        //User fromUser = service.findUserById(fromUserID);
        List<Message> messageList = service.getMessagesBetweenUsers(loggedUser.getId(), fromUserID);


        List<MessageDTO> messages = new ArrayList<>();
        for (Message message : messageList) {
            MessageDTO messageDTO;
            if (Objects.equals(message.getSender().getId(), loggedUser.getId())) {
                messageDTO = new MessageDTO("", message.getMessage());
            } else {
                messageDTO = new MessageDTO(message.getMessage(), "");
            }
            messages.add(messageDTO);
        }

        messagesList.setAll(messages);


    }

    @FXML
    public void onSendMessageButton(){
        String messageText = messageTextField.getText();
        try{
            int id_receipentUser = friendsTableView.getSelectionModel().getSelectedItem().getUID();
            service.addMessage(loggedUser.getId(),id_receipentUser,messageText);


        }
        catch (RepoException ignore){

        }
    }



    @FXML
    public void setBackButton(){
        chatPane.setVisible(false);
    }



}