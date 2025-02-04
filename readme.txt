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


server:
import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Scanner;

public class Server {
    public static void main(String[] args) throws IOException {
        ServerSocket serverSocket = new ServerSocket(1555);
        System.out.println("Server is running and waiting for a client...");

        Socket clientSocket = serverSocket.accept();
        System.out.println("Client connected.");

        InputStream clientIn = clientSocket.getInputStream();
        DataInputStream dis = new DataInputStream(clientIn);

        OutputStream clientOut = clientSocket.getOutputStream();
        DataOutputStream dos = new DataOutputStream(clientOut);

        Scanner sc = new Scanner(System.in);

        dos.writeUTF("Hello client! Your name?\nPress q to exit");

        while (true) {
            String clientInput = dis.readUTF();
            System.out.println("Client: " + clientInput);

            if (clientInput.equals("q")) {
                break;
            }

            System.out.print("Server: ");
            String serverReply = sc.nextLine();
            dos.writeUTF(serverReply);

            if (serverReply.equals("q")) {
                break;
            }
        }

        dis.close();
        dos.close();
        clientSocket.close();
        serverSocket.close();
    }
}