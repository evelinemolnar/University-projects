package app.salesagency.controller;

import app.salesagency.model.Agent;
import app.salesagency.model.Order;
import app.salesagency.model.Product;
import app.salesagency.model.Agent;
import app.salesagency.service.IObserver;
import app.salesagency.service.Service;
import app.salesagency.exceptions.MyException;
import app.salesagency.service.Service;
import javafx.animation.KeyFrame;
import javafx.animation.Timeline;
import javafx.application.Platform;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;
import javafx.util.Duration;


import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

public class AgentController implements IObserver {

    private final Duration refreshInterval = Duration.seconds(5);

    private Service service;
    private Agent loggedAgent=null;
    private Stage loginStage;


    @FXML
    private TableView<Product> productsTableView;
    @FXML
    private TableColumn<Product, String> denumireColumn;
    @FXML
    private TableColumn<Product, Integer> cantitateColumn;
    @FXML
    private TableColumn<Product, Double> pretColumn;
    @FXML
    private Label listaProduseLabel;
    @FXML
    private Button comandaButton;
    @FXML
    private Spinner<Integer> cantitateSpinner;
    @FXML
    private TextField numeClientTextField;
    @FXML
    private TextField adresaClientTextField;
    @FXML
    private TextField telefonClientTextField;
    @FXML
    private Button refreshButton;
    @FXML
    private Button LogOutButton;
    ObservableList<Product> produseList = FXCollections.observableArrayList();

    private void startAutoRefresh() {
        Timeline timeline = new Timeline(new KeyFrame(refreshInterval, event -> {
            onRefresh();
        }));
        timeline.setCycleCount(Timeline.INDEFINITE);
        timeline.play();
    }

    public void init() {
        init_lists();
        initialize();
        startAutoRefresh();
    }
    public void init_lists()
    {
        List<Product> list = (List<Product>) service.getAllProducts();
        produseList.setAll(list);

    }
    @FXML
    public void initialize() {
        denumireColumn.setCellValueFactory(new PropertyValueFactory<>("name"));
        pretColumn.setCellValueFactory(new PropertyValueFactory<>("price"));
        cantitateColumn.setCellValueFactory(new PropertyValueFactory<>("stock"));
        productsTableView.setItems(produseList);

    }

    @FXML
    public void onSelectedItemTable() {
        Product product = productsTableView.getSelectionModel().getSelectedItem();
        if (product != null) {
            cantitateSpinner.setValueFactory(new SpinnerValueFactory.IntegerSpinnerValueFactory(1, product.getStock()));
        }
    }



    public void logout() {
        try {
            service.logoutAgent(loggedAgent);
            loginStage.show();
        } catch (MyException e) {
            System.out.println("Logout error " + e);
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }
    public void onLogoutButtonAction() {
        logout();
        Stage stage = (Stage) this.cantitateSpinner.getScene().getWindow();
        stage.close();
    }

    public void onRefresh() {
        init_lists();
        initialize();
    }

    @Override
    public void showAgents() {

    }

    public void showProducts() {
        Platform.runLater(() -> {
            init_lists();
        });
    }

    @Override
    public void showOrders() {

    }

    @FXML
    public void onPlaceOrderButtonAction(){
        try{
            Product produs = service.getProduct(productsTableView.getSelectionModel().getSelectedItem().getId());
            int cantitate = cantitateSpinner.getValue();

            if(produs == null){
                Alert alert = new Alert(Alert.AlertType.ERROR);
                alert.setTitle("Error");
                alert.setContentText("No product selected.");
                alert.showAndWait();
                return;
            }
            else if(cantitate > produs.getStock()){
                Alert alert = new Alert(Alert.AlertType.ERROR);
                alert.setTitle("Error");
                alert.setContentText("Not enough products in stock.");
                alert.showAndWait();
                return;
            }
            else {
                Order order = new Order(loggedAgent.getId(), produs.getId(), cantitate);
                service.addOrder(order);
                Update(order);
                onRefresh();
                Alert alert = new Alert(Alert.AlertType.INFORMATION);
                alert.setTitle("Success");
                alert.setContentText("Order placed successfully.");
                alert.showAndWait();
            }
        }
        catch (NullPointerException npe) {
            Alert alert = new Alert(Alert.AlertType.WARNING, npe.getMessage(), ButtonType.OK);
            alert.show();
        } catch (Exception ex) {
            Alert alert = new Alert(Alert.AlertType.ERROR, ex.getMessage(), ButtonType.OK);
            alert.show();
        }
    }

    public void Update(Order order){
        try {

            int newquantity = order.getQuantity();
            Product product = service.getProduct(order.getProduct_id());
            product.setName(product.getName());
            product.setPrice(product.getPrice());
            product.setStock(product.getStock()-newquantity);

            service.updateProduct(product);
            onRefresh();
        } catch (Exception e) {
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle("Error");
            alert.setContentText(e.getMessage());
            alert.showAndWait();
        }
    }


    public void SetService(Service service) {
        this.service = service;
        init();
    }

    public void SetAgent(Agent currentAgent) {
        this.loggedAgent = currentAgent;
    }

    public void setStage(Stage window) {
        this.loginStage = window;
    }
}
