import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

public class EchoServer {
    public static final int PORT = 1050; // Server port
    public static final String SECRET = "mischief-managed"; // Server secret
    public static final String STOP = "STOP"; // Server secret

    public static void main(String[] args) {
        ServerSocket serverSocket = null;
        try {
            serverSocket = new ServerSocket(PORT);
        } catch (IOException e) {
            e.printStackTrace();
        }
        System.out.println("EchoServer: started ");
        System.out.println("Server Socket: " + serverSocket);
        Socket clientSocket = null;

        try {
            // Waits until connection is available
            clientSocket = serverSocket.accept();
            new ReaderStream(clientSocket);
            new OutStream(clientSocket);
        }
        catch (IOException e) {
            System.err.println("Accept failed");
            System.exit(1);
        }
    }
}