package app.salesagency.model;

public interface Entity<ID>{
    ID getId();

    void setId(ID id);

}