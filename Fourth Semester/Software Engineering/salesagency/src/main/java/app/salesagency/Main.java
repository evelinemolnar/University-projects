package app.salesagency;

import java.io.IOException;

import app.salesagency.controller.AdminController;
import app.salesagency.controller.AgentController;
import app.salesagency.controller.LoginController;
import app.salesagency.repository.utils.HibernateUtils;
import app.salesagency.service.Service;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;
import org.hibernate.SessionFactory;

public class Main extends Application{
    @Override
    public void start(Stage stage) throws IOException{
        FXMLLoader fxmlLoader = new FXMLLoader(Main.class.getResource("login-view.fxml"));
        Scene scene = new Scene(fxmlLoader.load(), 400, 400);
        LoginController controller=fxmlLoader.getController();
        SessionFactory sessionFactory = HibernateUtils.initialize();
        controller.SetService(Service.getInstance(sessionFactory));

        FXMLLoader adminLoader = new FXMLLoader(Main.class.getResource("admin-view.fxml"));
        Parent parentForAdmin=adminLoader.load();
        AdminController adminController =adminLoader.getController();
        adminController.SetService(Service.getInstance(sessionFactory));
        controller.setAdminController(adminController);
        controller.setParentForAdmin(parentForAdmin);

        FXMLLoader agentLoader = new FXMLLoader(Main.class.getResource("main-view.fxml"));
        Parent parentForAgent=agentLoader.load();
        AgentController agentController =agentLoader.getController();
        agentController.SetService(Service.getInstance(sessionFactory));
        controller.setAgentController(agentController);
        controller.setParentForAgent(parentForAgent);

        stage.setTitle("LogIn");
        stage.setScene(scene);
        stage.show();
    }
}
