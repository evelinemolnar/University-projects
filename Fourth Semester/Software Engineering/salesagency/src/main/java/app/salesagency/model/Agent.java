package app.salesagency.model;

import javax.persistence.*;
import javax.persistence.Entity;

@Entity
@Table(name = "Agents")
public class Agent implements app.salesagency.model.Entity<Integer>{
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private int id;
    @Column(name = "name")
    private String name;
    @Column(name = "username")
    private String username;
    @Column(name = "password")
    private String password;

    public Agent(String name, String username, String password) {
        this.name = name;
        this.username = username;
        this.password = password;
    }
    public Agent() {
    }

    @Override
    public Integer getId(){
        return id;
    }

    @Override
    public void setId(Integer id){
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getUsername() {
        return username;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }
}
