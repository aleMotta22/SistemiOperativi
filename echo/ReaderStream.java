import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.Socket;

public class ReaderStream extends Thread {
    private final BufferedReader in;
    private final Socket socket;
    public ReaderStream(Socket socket) throws IOException {
        this.socket = socket;
        this.in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
        start();
    }

    @Override
    public void run() {
        super.run();
        String read;
        while (true) {
            try{
                read = in.readLine();
                if (read.equalsIgnoreCase(EchoServer.STOP)) {
                    System.out.println("Killing Server with SECRET: " + read);
                    break;
                }
                System.out.println("Ricevuto : " + read);
            }catch (Exception ex){
                if(socket == null || socket.isClosed())
                    break;
                ex.printStackTrace();
            }
        }
        try {
            in.close();
            if(socket != null && !socket.isClosed())
                socket.close();
        }catch (Exception ex){
            ex.printStackTrace();
        }

    }
}