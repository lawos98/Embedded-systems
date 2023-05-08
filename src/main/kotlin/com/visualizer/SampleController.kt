package com.visualizer

import com.fazecast.jSerialComm.SerialPort
import javafx.application.Platform
import javafx.collections.FXCollections
import javafx.fxml.FXML
import javafx.scene.chart.LineChart
import javafx.scene.chart.XYChart
import javafx.scene.control.Label
import java.net.URL
import java.util.*

class SampleController : javafx.fxml.Initializable {
    @FXML
    lateinit var beatLabel: Label
    @FXML
    lateinit var bassLabel: Label
    @FXML
    lateinit var peakLabel: Label
    @FXML
    lateinit var chart: LineChart<Number, Number>

    private val beatData = FXCollections.observableArrayList<XYChart.Data<Number, Number>>()
    private val bassData = FXCollections.observableArrayList<XYChart.Data<Number, Number>>()
    private val peakData = FXCollections.observableArrayList<XYChart.Data<Number, Number>>()
    private var count = 0

    override fun initialize(location: URL?, resources: ResourceBundle?) {
        chart.xAxis.label = "Sample"
        chart.yAxis.label = "Value"
        chart.createSymbols = false

        val beatSeries = XYChart.Series<Number, Number>()
        beatSeries.name = "Beat"
        beatSeries.data = beatData
        chart.data.add(beatSeries)

        val bassSeries = XYChart.Series<Number, Number>()
        bassSeries.name = "Bass"
        bassSeries.data = bassData
        chart.data.add(bassSeries)

        val peakSeries = XYChart.Series<Number, Number>()
        peakSeries.name = "Peak"
        peakSeries.data = peakData
        chart.data.add(peakSeries)

        Thread {
            val port = SerialPort.getCommPort("/dev/ttyACM0")
            port.setBaudRate(9600)
            port.openPort()

            val buffer = ByteArray(1024)
            var bytesRead: Int
            var str = ""
            while (true) {
                bytesRead = port.readBytes(buffer, buffer.size.toLong())
                if (bytesRead > 0) {
                    str += String(buffer, 0, bytesRead)
                    if (str.contains("\n")) {
                        val lines = str.split("\n")
                        str = lines.last()
                        lines.dropLast(1).forEach { line ->
                            Platform.runLater {
                                val values = line.split(",")
                                if (values.size == 3) {
                                    val beatValue = values[0].toDouble()
                                    val bassValue = values[1].toDouble()
                                    val peakValue = values[2].toDouble()

                                    beatData.add(XYChart.Data(count, beatValue))
                                    bassData.add(XYChart.Data(count, bassValue))
                                    peakData.add(XYChart.Data(count, peakValue))

                                    beatLabel.text = beatValue.toString()
                                    bassLabel.text = bassValue.toString()
                                    peakLabel.text = peakValue.toString()

                                    count++
                                }
                            }
                        }
                    }
                }
            }
        }.start()
    }
}