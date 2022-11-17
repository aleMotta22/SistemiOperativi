import java.io.IOException;
import java.net.InetAddress;
import java.net.Socket;
import java.net.UnknownHostException;

public class EchoClient {
    public static void main(String[] args) throws IOException {
        InetAddress addr;
        if (args.length == 0)
            addr = InetAddress.getByName(null);
        else addr = InetAddress.getByName(args[0]);

        Socket socket = null;
        try {
            // Create socket
            socket = new Socket(addr, EchoServer.PORT);
            System.out.println("EchoClient: started");
            System.out.println("Client Socket: " + socket);
            new ReaderStream(socket);
            new OutStream(socket);
        } catch (UnknownHostException e) {
            System.err.println("Don't know about host " + addr);
            System.exit(1);
        } catch (IOException e) {
            System.err.println("Couldn't get I/O for the connection to: " + addr);
            System.exit(1);
        }
    }
}