import javax.swing.*;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.nio.charset.StandardCharsets;

public class CustomOutputStream extends OutputStream {
    private final JTextArea textArea;
    private final ByteArrayOutputStream buffer;

    public CustomOutputStream(JTextArea textArea) {
        this.textArea = textArea;
        this.buffer = new ByteArrayOutputStream();
    }

    @Override
    synchronized public void write(int b) throws IOException {
        // Store the byte in the buffer
        buffer.write(b);

        // Check if it's a new line character
        if (b == '\n') {
            // Convert the buffered bytes to a string using UTF-8 encoding
            String line = buffer.toString(StandardCharsets.UTF_8);
            textArea.append(line);
            textArea.setCaretPosition(textArea.getDocument().getLength());
            buffer.reset();
        }
    }
}
