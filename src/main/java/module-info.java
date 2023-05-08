module com.visualizer {
    requires javafx.controls;
    requires javafx.fxml;
    requires kotlin.stdlib;
    requires com.fazecast.jSerialComm;


    opens com.visualizer to javafx.fxml;
    exports com.visualizer;
}