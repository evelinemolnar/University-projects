package app.salesagency.controller;

import app.salesagency.Main;
import app.salesagency.model.Admin;
import app.salesagency.model.Agent;
import app.salesagency.exceptions.MyException;
import app.salesagency.service.IObserver;
import app.salesagency.service.Service;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;

import java.io.IOException;

public class LoginController {

    @FXML
    public TextField usernameField;
    @FXML
    public PasswordField passwordField;
    @FXML
    public Label messageToUser;
    @FXML

    public Button signInButton;
    private Admin currentAdmin;
    private Agent currentAgent;
    private AdminController adminController;
    private AgentController agentController;
    private Parent parentForAdmin, parentForAgent;
    Service service;

    @FXML
    public AnchorPane loginPane;


    public void SetService(Service s){
        this.service = s;
        loginPane.setVisible(true);
    }

    public void setAdminController(AdminController adminController) {
        this.adminController = adminController;
    }

    public void setAgentController(AgentController agentController) {
        this.agentController = agentController;
    }

    public void setParentForAdmin(Parent parentForAdmin) {
        this.parentForAdmin = parentForAdmin;
    }

    public void setParentForAgent(Parent parentForAgent) {
        this.parentForAgent = parentForAgent;
    }
    
    @FXML
    public void initialize() throws IOException {

        usernameField.setText("");
        passwordField.setText("");

        usernameField.setPromptText("username");
        passwordField.setPromptText("password");
        messageToUser.setText("");

    }

    @FXML
    public void handleSubmitButtonAction(ActionEvent actionEvent) throws IOException {

        String username = usernameField.getText();
        String password = passwordField.getText();
        Object admin = service.findAdminByUsername(username);
        try{
            if(admin==null) {
                Object agent = service.findAgentByUsername(username);
                if(agent==null)
                {
                    Alert alert = new Alert(Alert.AlertType.ERROR, "Account doesn't exist", ButtonType.OK);
                    alert.show();
                }
                else {
                    Agent tryingP = new Agent(null,username, password);
                    currentAgent = service.loginAgent(tryingP, (IObserver) agentController);
                    changeSceneAgent();
                }
            }
            else {
                Admin tryingA = new Admin(null,username, password);
                currentAdmin = service.loginAdmin(tryingA, (IObserver) adminController);
                changeSceneAdmin();
            }
        }
        catch(Exception e) {
            Alert alert = new Alert(Alert.AlertType.ERROR, e.getMessage(), ButtonType.OK);
            alert.show();
        }


    }

    private void changeSceneAgent() {
        FXMLLoader loader=new FXMLLoader(Main.class.getResource("main-view.fxml"));
        Scene scene;
        try{
            scene = new Scene(loader.load(), 600, 400);
            AgentController controller = loader.getController();
            controller.SetService(service);
            controller.SetAgent(currentAgent);
            controller.setStage((Stage) usernameField.getScene().getWindow());

            Stage currentStage=(Stage) signInButton.getScene().getWindow();

            Stage newStage = new Stage();
            newStage.setScene(scene);
            newStage.setResizable(false);
            newStage.setTitle("Agent");
            currentStage.close();
            newStage.show();
            usernameField.setText("");
            passwordField.setText("");
        }
        catch (Exception ex) {
            ex.printStackTrace();
        }
    }

    private void changeSceneAdmin() {
        FXMLLoader loader=new FXMLLoader(Main.class.getResource("admin-view.fxml"));
        Scene scene;
        try{
            scene = new Scene(loader.load(), 600, 400);
            AdminController controller = loader.getController();
            controller.SetService(service);
            controller.SetAdmin(currentAdmin);
            controller.setStage((Stage) usernameField.getScene().getWindow());

            Stage currentStage=(Stage) signInButton.getScene().getWindow();

            Stage newStage = new Stage();
            newStage.setScene(scene);
            newStage.setResizable(false);
            newStage.setTitle("Admin");
            currentStage.close();
            newStage.show();
            usernameField.setText("");
            passwordField.setText("");
        }
        catch (Exception ex) {
            ex.printStackTrace();
        }
    }


}
