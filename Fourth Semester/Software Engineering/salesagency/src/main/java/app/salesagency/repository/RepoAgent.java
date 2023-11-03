package app.salesagency.repository;

import app.salesagency.exceptions.MyException;
import app.salesagency.model.Agent;
import app.salesagency.repository.interfaces.IRepoAgent;
import org.hibernate.Session;
import org.hibernate.SessionFactory;
import org.hibernate.Transaction;

public class RepoAgent implements IRepoAgent {
    private final SessionFactory sessionFactory;
    public RepoAgent(SessionFactory sessionFactory) {
        this.sessionFactory = sessionFactory;
    }

    @Override
    public void add(Agent entity) {
        try(Session session = sessionFactory.openSession()){
            session.beginTransaction();
            session.save(entity);
            session.getTransaction().commit();
        }
    }

    @Override
    public void remove(Integer id) {
        try(Session session = sessionFactory.openSession()){
            Transaction tx=null;
            try{
                tx = session.beginTransaction();
                String hql = "from Agent where id=:id";
                Agent Agent = session.createQuery(hql, Agent.class)
                        .setParameter("id", id)
                        .setMaxResults(1)
                        .uniqueResult();
                session.delete(Agent);
                tx.commit();
            } catch(RuntimeException ex){
                if (tx!=null)
                    tx.rollback();
            }
        }
    }

    @Override
    public void update(Agent Agent) {
        try(Session session = sessionFactory.openSession()){
            Transaction tx=null;
            try{
                tx = session.beginTransaction();
                session.update(Agent);
                tx.commit();
            } catch(RuntimeException ex){
                if (tx!=null)
                    tx.rollback();
            }
        }
    }

    @Override
    public Agent findElement(Integer id) {
        try(Session session=sessionFactory.openSession()){
            Transaction transaction=null;
            try {
                transaction=session.beginTransaction();
                Agent Agent=session.createQuery("from Agent where id=:id",Agent.class)
                        .setParameter("id",id)
                        .setMaxResults(1)
                        .uniqueResult();
                transaction.commit();
                return Agent;
            }
            catch (RuntimeException ex){
                if(transaction!=null)
                    transaction.rollback();
            }

        }
        return null;
    }

    @Override
    public Iterable<Agent> getAll() {
        try(Session session = sessionFactory.openSession()){
            session.beginTransaction();
            Iterable<Agent> Agents = session.createQuery("from Agent", Agent.class).list();
            session.getTransaction().commit();
            return Agents;
        }
    }
    public Object authenticateAgent(String username, String password) throws MyException{
        try(Session session = sessionFactory.openSession()) {
            session.beginTransaction();
            Object Agent = session.createQuery("from Agent where username = :username and password = :password")
                    .setParameter("username", username)
                    .setParameter("password", password)
                    .uniqueResult();
            session.getTransaction().commit();
            if (Agent == null) {
                throw new MyException("Username sau parola gresita!");
            }
            return Agent;
        }
    }
}

