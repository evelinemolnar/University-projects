package app.salesagency.model;

import javax.persistence.*;
import javax.persistence.Entity;

@Entity
@Table(name = "Orders")
public class Order implements app.salesagency.model.Entity<Integer>{

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private int id;
    @Column(name = "agent_id")
    private int agent_id;
    @Column(name = "product_id")
    private int product_id;
    @Column(name = "quantity")
    private int quantity;

    public Order(int agent_id, int product_id, int quantity) {
        this.agent_id = agent_id;
        this.product_id = product_id;
        this.quantity = quantity;
    }

    public Order() {
    }

    @Override
    public Integer getId(){
        return id;
    }

    @Override
    public void setId(Integer id){
        this.id = id;
    }

    public int getAgent_id() {
        return agent_id;
    }

    public void setAgent_id(int agent_id){
        this.agent_id = agent_id;
    }

    public int getProduct_id() {
        return product_id;
    }

    public void setProduct_id(int product_id){
        this.product_id = product_id;
    }

    public int getQuantity() {
        return quantity;
    }

    public void setQuantity(int quantity){
        this.quantity = quantity;
    }
}

