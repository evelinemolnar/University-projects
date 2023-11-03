package app.salesagency.controller;

import app.salesagency.model.Admin;
import app.salesagency.model.Agent;
import app.salesagency.model.Product;
import app.salesagency.model.Admin;
import app.salesagency.service.IObserver;
import app.salesagency.service.Service;
import app.salesagency.exceptions.MyException;
import app.salesagency.service.Service;
import javafx.animation.KeyFrame;
import javafx.animation.Timeline;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.stage.Stage;

import javafx.util.Duration;
import java.util.ArrayList;
import java.util.List;

public class AdminController implements IObserver {
    Service service;
    private final Duration refreshInterval = Duration.seconds(5);

    private Admin loggedAdmin = null;

    private Stage loginStage;
    @FXML
    public Button LogOutButton;
    @FXML
    private TableView<Agent> agentiTableView;
    @FXML
    private TableView<Product> productsTableView;
    @FXML
    private TableColumn<Product, String> usernameColumn;
    @FXML
    private TableColumn<Product, String> passwordColumn;
    @FXML
    private TableColumn<Product, String> nameColumn;
    @FXML
    private TableColumn<Product, String> priceColumn;
    @FXML
    private TableColumn<Product, String> quantityColumn;
    @FXML
    private Button addAgentButton;
    @FXML
    private Button deleteAgentButton;
    @FXML
    private TextField usernameTextField;
    @FXML
    private TextField passwordTextField;
    @FXML
    private TextField nameTextField;

    @FXML
    private TextField priceTextField;

    @FXML
    private TextField quantityTextField;
    @FXML
    private Button addProductButton;
    @FXML
    private Button deleteProductButton;
    @FXML
    private Button updateProductButton;
    @FXML
    private Button updateAgentButton;

    @FXML
    private Button refreshButton;

    private ObservableList<Agent> agentiObservableList = FXCollections.observableArrayList();

    private ObservableList<Product> produseObservableList = FXCollections.observableArrayList();




    public void setStage(Stage stage){
        this.loginStage = stage;
    }


    public void SetService(Service service) {
        this.service = service;
        init_lists();
        initialize();
        startAutoRefresh();
    }
    public void SetAdmin(Admin admin)
    {
        this.loggedAdmin = admin;
    }

    @FXML
    public void initialize() {
        nameColumn.setCellValueFactory(new PropertyValueFactory<>("name"));
        priceColumn.setCellValueFactory(new PropertyValueFactory<>("price"));
        quantityColumn.setCellValueFactory(new PropertyValueFactory<>("stock"));
        productsTableView.setItems(produseObservableList);
        usernameColumn.setCellValueFactory(new PropertyValueFactory<>("username"));
        passwordColumn.setCellValueFactory(new PropertyValueFactory<>("password"));
        agentiTableView.setItems(agentiObservableList);
    }

    private void startAutoRefresh() {
        Timeline timeline = new Timeline(new KeyFrame(refreshInterval, event -> {
            onRefresh();
        }));
        timeline.setCycleCount(Timeline.INDEFINITE);
        timeline.play();
    }
    public void onRefresh() {
        init_lists();
        initialize();
    }
    @FXML
    public void init_lists() {
        List<Product> produse = (List<Product>) service.getAllProducts();
        produseObservableList = FXCollections.observableArrayList(produse);

        List<Agent> agenti = (List<Agent>) service.getAllAgents();
        agentiObservableList = FXCollections.observableArrayList(agenti);
    }



    @FXML
    public void onLogoutButtonAction(){
        logout();
        Stage stage = (Stage) this.usernameTextField.getScene().getWindow();
        stage.close();
    }

    public void logout() {
        try {
            service.logoutAdmin(loggedAdmin);
            loginStage.show();
        } catch (MyException e) {
            System.out.println("Logout error " + e);
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }

    @FXML
    public void onAddAgentButtonAction(){
        try {
            String name = "name";
            String username = usernameTextField.getText();
            String password = passwordTextField.getText();
            Agent agent = new Agent(name, username, password);
            service.addAgent(agent);
            usernameTextField.clear();
            passwordTextField.clear();
            onRefresh();
        } catch (NullPointerException npe) {
            Alert alert = new Alert(Alert.AlertType.WARNING, npe.getMessage(), ButtonType.OK);
            alert.show();
        } catch (Exception ex) {
            Alert alert = new Alert(Alert.AlertType.ERROR, ex.getMessage(), ButtonType.OK);
            alert.show();
        }
    }

    @FXML
    public void onDeleteAgentButtonAction(){
        try {
            Agent agent = agentiTableView.getSelectionModel().getSelectedItem();
            service.removeAgent(agent.getId());
            onRefresh();
        } catch (NullPointerException npe) {
            Alert alert = new Alert(Alert.AlertType.WARNING, npe.getMessage(), ButtonType.OK);
            alert.show();
        } catch (Exception ex) {
            Alert alert = new Alert(Alert.AlertType.ERROR, ex.getMessage(), ButtonType.OK);
            alert.show();
        }
    }


    @FXML
    public void onAddProductButtonAction(){
        try {
            String name = nameTextField.getText();
            int price = Integer.parseInt(priceTextField.getText());
            int quantity = Integer.parseInt(quantityTextField.getText());
            Product product = new Product(name, price, quantity);
            nameTextField.clear();
            priceTextField.clear();
            quantityTextField.clear();
            service.addProduct(product);
            onRefresh();
        } catch (Exception e) {
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle("Error");
            alert.setContentText(e.getMessage());
            alert.showAndWait();
        }
    }

    @FXML
    public void onDeleteProductButtonAction(){
        try {
            Product product = productsTableView.getSelectionModel().getSelectedItem();
            service.removeProduct(product.getId());
            onRefresh();
        } catch (Exception e) {
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle("Error");
            alert.setContentText(e.getMessage());
            alert.showAndWait();
        }
    }

    @FXML
    public void onUpdateProductButtonAction(){
        try {
            Product product =service.getProduct(productsTableView.getSelectionModel().getSelectedItem().getId());
            String name = nameTextField.getText();
            int price = Integer.parseInt(priceTextField.getText());
            int quantity = Integer.parseInt(quantityTextField.getText());

            product.setName(name);
            product.setPrice(price);
            product.setStock(quantity);

            service.updateProduct(product);
            onRefresh();
            nameTextField.clear();
            priceTextField.clear();
            quantityTextField.clear();
        } catch (NullPointerException npe) {
            Alert alert = new Alert(Alert.AlertType.WARNING, npe.getMessage(), ButtonType.OK);
            alert.show();
        } catch (Exception ex) {
            Alert alert = new Alert(Alert.AlertType.ERROR, ex.getMessage(), ButtonType.OK);
            alert.show();
        }
    }

    @FXML
    public void onUpdateAgentButtonAction(){
        try {
            Agent agent = service.getAgent(agentiTableView.getSelectionModel().getSelectedItem().getId());
            String username = usernameTextField.getText();
            String password = passwordTextField.getText();

            agent.setUsername(username);
            agent.setPassword(password);

            usernameTextField.clear();
            passwordTextField.clear();

            service.updateAgent(agent);
            onRefresh();
        } catch (NullPointerException npe) {
            Alert alert = new Alert(Alert.AlertType.WARNING, npe.getMessage(), ButtonType.OK);
            alert.show();
        } catch (Exception ex) {
            Alert alert = new Alert(Alert.AlertType.ERROR, ex.getMessage(), ButtonType.OK);
            alert.show();
        }
    }


    @Override
    public void showAgents() {

    }

    @Override
    public void showProducts() {

    }

    @Override
    public void showOrders() {

    }
}
