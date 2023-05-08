package com.visualizer

import javafx.application.Application
import javafx.fxml.FXMLLoader
import javafx.scene.Scene
import javafx.scene.layout.VBox
import javafx.stage.Stage

class HelloApplication : Application() {
    override fun start(primaryStage: Stage) {
        val loader = FXMLLoader(javaClass.getResource("main.fxml"))
        val root = loader.load<VBox>()
        primaryStage.title = "Serial Port Data"
        primaryStage.scene = Scene(root, 800.0, 600.0)
        primaryStage.show()
    }
}

fun main() {
    Application.launch(HelloApplication::class.java)
}