client:-

import java.io.*;
import java.net.Socket;
import java.util.Scanner;

public class Client {
    public static void main(String[] args) throws IOException {
        Socket socket = new Socket("localhost", 1555);

        InputStream socketIn = socket.getInputStream();
        DataInputStream dis = new DataInputStream(socketIn);

        OutputStream socketOut = socket.getOutputStream();
        DataOutputStream dos = new DataOutputStream(socketOut);

        Scanner sc = new Scanner(System.in);

        while (true) {
            String serverMessage = dis.readUTF();
            System.out.println("Server: " + serverMessage);

            if (serverMessage.equals("q")) {
                break;
            }

            String clientInput = sc.nextLine();
            dos.writeUTF(clientInput);

            if (clientInput.equals("q")) {
                break;
            }
        }

        dis.close();
        dos.close();
        socketIn.close();
        socketOut.close();
        socket.close();
    }
}