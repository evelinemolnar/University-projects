package com.socialnetwork.app;

import com.socialnetwork.app.controllers.LoginInterfaceController;
import com.socialnetwork.app.domain.Friendship;
import com.socialnetwork.app.domain.Message;
import com.socialnetwork.app.domain.User;
import com.socialnetwork.app.domain.validation.FriendshipValidator;
import com.socialnetwork.app.domain.validation.UserValidator;
import com.socialnetwork.app.domain.validation.Validator;
import com.socialnetwork.app.repository.AbstractRepo;
import com.socialnetwork.app.repository.FriendshipRepo;
import com.socialnetwork.app.repository.MessageRepo;
import com.socialnetwork.app.repository.UserRepo;
import com.socialnetwork.app.service.AppService;
import com.socialnetwork.app.service.Service;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.IOException;

public class Main extends Application {
    private final static String url="jdbc:postgresql://localhost:5432/lab2";
    private final static String username="postgres";
    private final static String password="2626";

    private static final Validator<User> userValidator=UserValidator.getInstance();
    private static final Validator<Friendship> friendshipValidator=FriendshipValidator.getInstance();
    private static final AbstractRepo<User> userRepository=new UserRepo(url,username,password);
    private static final AbstractRepo<Friendship> friendshipRepo =new FriendshipRepo(url,username,password, (UserRepo) userRepository);
    private static final AbstractRepo<Message> messageRepo =new MessageRepo(url,username,password, (UserRepo) userRepository);
    private static final Service service=new AppService((UserRepo) userRepository, (FriendshipRepo) friendshipRepo,(MessageRepo) messageRepo, userValidator,friendshipValidator);





    @Override
    public void start(Stage stage) throws IOException {

        FXMLLoader fxmlLoader = new FXMLLoader(Main.class.getResource("LoginInterfaceView.fxml"));
        Scene scene = new Scene(fxmlLoader.load(), 290, 400);
        LoginInterfaceController controller = fxmlLoader.getController();
        controller.setService((AppService) service);
        stage.setScene(scene);
        stage.setTitle("SocialNetwork");
        stage.setResizable(false);
        stage.show();
    }

    public static void main(String[] args) {
        launch();
    }
}