package com.socialnetwork.app.domain;


import java.util.Objects;

public class User extends Entity<Integer> {

    public String getLastName() {
        return lastName;
    }

    public String getFirstName() {
        return firstName;
    }

    public String getEmail() {
        return email;
    }

    private String lastName;
    private String firstName;
    private String email;

    public User(String nume, String prenume, String email) {
        this.lastName = nume;
        this.firstName = prenume;
        this.email = email;
    }


    @Override
    public String toString() {

        return firstName+" "+lastName+"\n";
    }

    /**
     * @return String print format
     */
    public String printPatternString() {
        return "ID: " + getId() + " First Name: " + firstName + " Last Name: " + lastName + " Email: " + email;
    }

    /**
     * @return String csv format
     */
    @Override
    public String fileCsvPatternString() {
        return getId() + ";" + lastName + ";" + firstName + ";" + email + "\n";
    }


    @Override
    public void set(Entity other) {
        this.email = ((User) other).email;
        this.firstName = ((User) other).firstName;
        this.lastName = ((User) other).lastName;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        if (!super.equals(o)) return false;
        User user = (User) o;
        return Objects.equals(email, user.email);
    }

    @Override
    public int hashCode() {
        return Objects.hash(super.hashCode(), email);
    }
}