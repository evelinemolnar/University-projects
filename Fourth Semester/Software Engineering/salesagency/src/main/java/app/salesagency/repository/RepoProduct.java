package app.salesagency.repository;

import app.salesagency.model.Product;
import app.salesagency.repository.interfaces.IRepoProduct;
import org.hibernate.Session;
import org.hibernate.SessionFactory;
import org.hibernate.Transaction;

import java.util.List;

public class RepoProduct implements IRepoProduct {
    private final SessionFactory sessionFactory;
    public RepoProduct(SessionFactory sessionFactory) {
        this.sessionFactory = sessionFactory;
    }

    @Override
    public void add(Product entity) {
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
                String hql = "from Product where id=:id";
                Product Product = session.createQuery(hql, Product.class)
                        .setParameter("id", id)
                        .setMaxResults(1)
                        .uniqueResult();
                session.delete(Product);
                tx.commit();
            } catch(RuntimeException ex){
                if (tx!=null)
                    tx.rollback();
            }
        }
    }
    @Override
    public void update(Product Product) {
        try(Session session = sessionFactory.openSession()){
            Transaction tx=null;
            try{
                tx = session.beginTransaction();
                session.update(Product);
                tx.commit();
            } catch(RuntimeException ex){
                if (tx!=null)
                    tx.rollback();
            }
        }
    }
    @Override
    public Product findElement(Integer id) {
        try(Session session=sessionFactory.openSession()){
            Transaction transaction=null;
            try {
                transaction=session.beginTransaction();
                Product Product=session.createQuery("from Product where id=:id",Product.class)
                        .setParameter("id",id)
                        .setMaxResults(1)
                        .uniqueResult();
                transaction.commit();
                return Product;
            }
            catch (RuntimeException ex){
                if(transaction!=null)
                    transaction.rollback();
            }

        }
        return null;
    }

    @Override
    public Iterable<Product> getAll() {
        try(Session session=sessionFactory.openSession()){
            Transaction transaction=null;
            try{
                transaction=session.beginTransaction();
                List<Product> Products=session.createQuery("from Product",Product.class)
                        .list();
                transaction.commit();
                return Products;
            }
            catch (RuntimeException ex){
                if(transaction!=null)
                    transaction.rollback();
            }
        }
        return null;
    }
}
