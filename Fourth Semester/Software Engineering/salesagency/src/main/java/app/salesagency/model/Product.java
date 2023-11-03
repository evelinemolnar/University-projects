package app.salesagency.model;

import javax.persistence.*;
import javax.persistence.Entity;
@Entity
@Table(name = "Products")
public class Product implements app.salesagency.model.Entity<Integer> {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private int id;
    @Column(name = "name")
    private String name;

    @Column(name = "price")
    private Integer price;

    @Column(name = "stock")
    private Integer stock;

    public Product(String name, Integer price, Integer stock) {
        this.name = name;
        this.price = price;
        this.stock = stock;
    }

    public Product() {
    }

    @Override
    public Integer getId() {
        return id;
    }

    @Override
    public void setId(Integer integer) {
        this.id = integer;
    }


    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public Integer getPrice() {
        return price;
    }

    public void setPrice(Integer price) {
        this.price = price;
    }

    public Integer getStock() {
        return stock;
    }

    public void setStock(Integer stock) {
        this.stock = stock;
    }
}
