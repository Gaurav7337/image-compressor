import sys
from PyQt5.QtWidgets import QApplication, QMainWindow, QPushButton, QLineEdit, QLabel, QFileDialog, QMessageBox
import subprocess

class ImageCompressor(QMainWindow):
    def __init__(self):
        super().__init__()

        self.initUI()

    def initUI(self):
        self.setWindowTitle('Image Compressor')

        # Input File Path
        self.inputLabel = QLabel('Input File:', self)
        self.inputLabel.move(20, 20)
        self.inputLineEdit = QLineEdit(self)
        self.inputLineEdit.setGeometry(100, 20, 280, 20)
        self.browseInputButton = QPushButton('Browse', self)
        self.browseInputButton.setGeometry(390, 20, 80, 20)
        self.browseInputButton.clicked.connect(self.browseInput)

        # Output File Path
        self.outputLabel = QLabel('Output File:', self)
        self.outputLabel.move(20, 60)
        self.outputLineEdit = QLineEdit(self)
        self.outputLineEdit.setGeometry(100, 60, 280, 20)
        self.browseOutputButton = QPushButton('Browse', self)
        self.browseOutputButton.setGeometry(390, 60, 80, 20)
        self.browseOutputButton.clicked.connect(self.browseOutput)

        # Quality (for JPEG)
        self.qualityLabel = QLabel('Quality (1-100):', self)
        self.qualityLabel.move(20, 100)
        self.qualityLineEdit = QLineEdit(self)
        self.qualityLineEdit.setGeometry(100, 100, 280, 20)
        self.qualityLineEdit.setText('80')  # Default quality

        # Execute Button
        self.executeButton = QPushButton('Execute', self)
        self.executeButton.setGeometry(20, 140, 450, 30)
        self.executeButton.clicked.connect(self.execute)

        self.setGeometry(300, 300, 500, 200)
        self.show()

    def browseInput(self):
        options = QFileDialog.Options()
        fileName, _ = QFileDialog.getOpenFileName(self, "Open Image File", "", "Images (*.png *.jpg *.bmp)", options=options)
        if fileName:
            self.inputLineEdit.setText(fileName)

    def browseOutput(self):
        options = QFileDialog.Options()
        fileName, _ = QFileDialog.getSaveFileName(self, "Save Image File", "", "Images (*.png *.jpg *.bmp)", options=options)
        if fileName:
            self.outputLineEdit.setText(fileName)

    def execute(self):
        inputFilePath = self.inputLineEdit.text()
        outputFilePath = self.outputLineEdit.text()
        quality = self.qualityLineEdit.text()

        if not inputFilePath or not outputFilePath:
            QMessageBox.warning(self, "Error", "Please specify both input and output file paths.")
            return

        try:
            quality_int = int(quality)
        except ValueError:
            QMessageBox.warning(self, "Error", "Quality must be an integer between 1 and 100.")
            return

        if quality_int < 1 or quality_int > 100:
            QMessageBox.warning(self, "Error", "Quality must be between 1 and 100.")
            return

        # Call the C++ command-line tool
        try:
            result = subprocess.run(['./image_compressor', 'compress', inputFilePath, outputFilePath, str(quality_int)],
                                    stdout=subprocess.PIPE, stderr=subprocess.PIPE)
            if result.returncode != 0:
                QMessageBox.warning(self, "Error", f"Failed to process the image.\n\n{result.stderr.decode('utf-8')}")
            else:
                QMessageBox.information(self, "Success", "Image processed successfully.")
        except Exception as e:
            QMessageBox.warning(self, "Error", str(e))

if __name__ == '__main__':
    app = QApplication(sys.argv)
    ex = ImageCompressor()
    sys.exit(app.exec_())
