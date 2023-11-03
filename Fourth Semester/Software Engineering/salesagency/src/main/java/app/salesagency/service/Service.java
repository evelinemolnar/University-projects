package app.salesagency.service;

import app.salesagency.exceptions.MyException;
import app.salesagency.model.Admin;
import app.salesagency.model.Agent;
import app.salesagency.model.*;
import app.salesagency.repository.RepoAdmin;
import app.salesagency.repository.RepoAgent;
import app.salesagency.repository.RepoOrder;
import app.salesagency.repository.RepoProduct;
import org.hibernate.SessionFactory;

import java.util.Map;
import java.util.Objects;
import java.util.concurrent.ConcurrentHashMap;

public class Service {
    private static Service instance;
    private final RepoAdmin adminRepo;
    private final RepoAgent agentRepo;
    private final RepoProduct productRepo;
    private final RepoOrder orderRepo;
    private final Map<Map<Integer, String>, IObserver> iObservers;

    public Service(RepoAdmin adminRepo, RepoAgent agentRepo, RepoProduct productRepo, RepoOrder orderRepo) {
        this.adminRepo=adminRepo;
        this.agentRepo=agentRepo;
        this.productRepo = productRepo;
        this.orderRepo = orderRepo;
        iObservers = new ConcurrentHashMap<>();
    }

    public static Service getInstance(SessionFactory sessionFactory){
        if(instance == null){
            instance = new Service(new RepoAdmin(sessionFactory),
                    new RepoAgent(sessionFactory),
                    new RepoProduct(sessionFactory),
                    new RepoOrder(sessionFactory));
        }
        return instance;
    }

    public synchronized Iterable<Admin> getAllAdmini() {
        return adminRepo.getAll();
    }
    public synchronized Iterable<Agent> getAllAgents() {
        return agentRepo.getAll();
    }
    public synchronized Iterable<Product> getAllProducts() {
        return productRepo.getAll();
    }


    public synchronized Admin loginAdmin(Admin admin, IObserver adminObserver) throws Exception {
        Admin admin2;
        try{
            admin2 = (Admin) adminRepo.authenticateAdmin(admin.getUsername(), admin.getPassword());
        } catch(MyException ex){
            throw ex;
        }
        if (admin2!=null){
            Map<Integer, String> key = Map.of(admin2.getId(), "admin");
            if(iObservers.get(key)!=null)
                throw new MyException("Admin already logged in.");
            iObservers.put(key, adminObserver);
        }
        else
            throw new MyException("Authentication failed.");
        return admin2;
    }

    public synchronized Agent loginAgent(Agent agent, IObserver agentObserver) throws Exception {
        Agent agent2;
        try{
            agent2 = (Agent) agentRepo.authenticateAgent(agent.getUsername(), agent.getPassword());
        } catch(MyException ex){
            throw ex;
        }
        if (agent2!=null){
            Map<Integer, String> key = Map.of(agent2.getId(), "agent");
            if(iObservers.get(key)!=null)
                throw new MyException("Agent already logged in.");
            iObservers.put(key, agentObserver);
        }
        else
            throw new MyException("Authentication failed.");
        return agent2;
    }

    public synchronized void logoutAdmin(Admin admin) throws MyException {
        Map<Integer, String> key = Map.of(admin.getId(), "admin");
        IObserver localClient= iObservers.remove(key);
        if (localClient==null)
            throw new MyException("Admin "+admin+" is not logged in.");
    }

    public synchronized void logoutAgent(Agent agent) throws MyException {
        Map<Integer, String> key = Map.of(agent.getId(), "agent");
        IObserver localClient= iObservers.remove(key);
        if (localClient==null)
            throw new MyException("Agent "+agent+" is not logged in.");
    }

    public Admin findAdminByUsername(String username)
    {
        Iterable<Admin> admini = getAllAdmini();
        for (Admin admin : admini) {
            String username2 = admin.getUsername();
            if (Objects.equals(username, username2))
                return admin;
        }
        return null;
    }

    public Agent findAgentByUsername(String username)
    {
        Iterable<Agent> agents = getAllAgents();
        for (Agent agent : agents) {
            String username2 = agent.getUsername();
            if (Objects.equals(username, username2))
                return agent;
        }
        return null;
    }

    public Agent getAgent(Integer id){return agentRepo.findElement(id);}

    public Product getProduct(Integer id){return productRepo.findElement(id);}

    public synchronized void addAgent(Agent agent)  {
        agentRepo.add(agent);
        for (IObserver iObserver: iObservers.values()) {
            iObserver.showAgents();
        }
    }
    public synchronized void removeAgent(Integer id)  {
        agentRepo.remove(id);
        for (IObserver iObserver: iObservers.values()) {
            iObserver.showAgents();
        }
    }
    public synchronized void updateAgent(Agent agent)  {
        agentRepo.update(agent);
        for (IObserver iObserver: iObservers.values()) {
            iObserver.showAgents();
        }
    }

    public synchronized void addProduct(Product product)  {
        productRepo.add(product);
        for (IObserver iObserver: iObservers.values()) {
            iObserver.showProducts();
        }
    }
    public synchronized void removeProduct(Integer id)  {
        productRepo.remove(id);
        for (IObserver iObserver: iObservers.values()) {
            iObserver.showProducts();
        }
    }
    public synchronized void updateProduct(Product product)  {
        productRepo.update(product);
        for (IObserver iObserver: iObservers.values()) {
            iObserver.showProducts();
        }
    }

    public synchronized void addOrder(Order order)  {
        orderRepo.add(order);
        for (IObserver iObserver: iObservers.values()) {
            iObserver.showOrders();
        }
    }



}
