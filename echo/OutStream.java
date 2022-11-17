import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;

public class OutStream extends Thread {
    private final BufferedReader in;
    private final PrintWriter writer;
    private final Socket socket;

    public OutStream(Socket socket) throws IOException {
        this.socket = socket;
        this.writer = new PrintWriter(socket.getOutputStream(), true);
        this.in = new BufferedReader(new InputStreamReader(System.in));
        start();
    }

    @Override
    public void run() {
        super.run();
        String read;
        boolean stop = false;
        while (!stop) {
            try{
                read = in.readLine();
                writer.println(read);
                if (read.equalsIgnoreCase(EchoServer.STOP)) {
                    System.out.println("Stopping");
                    stop = true;
                    break;
                }
            }catch (Exception ex){
                ex.printStackTrace();
            }
        }
        try {
            in.close();
            writer.close();
            socket.close();
        }catch (Exception ex){
            ex.printStackTrace();
        }

    }
}