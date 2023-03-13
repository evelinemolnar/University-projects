import java.net.*;
import java.io.*;

public class Client {

    public static void main(String args[]) throws Exception {
        try {
            Socket c = new Socket("127.0.0.1", 1234);

            BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));

            int nrmax;
            String s1;
            String s2;
            System.out.print("s1 = ");
            s1 = reader.readLine();
            System.out.print("s2 = ");
            s2 = reader.readLine();

            DataInputStream socketIn = new DataInputStream(c.getInputStream());
            DataOutputStream socketOut = new DataOutputStream(c.getOutputStream());
            int s1Length = s1.getBytes().length;
            int s2Length = s2.getBytes().length;
            socketOut.writeShort(s1Length);
            socketOut.write(s1.getBytes());
            socketOut.writeShort(s2Length);
            socketOut.write(s2.getBytes());
            socketOut.flush();
            int ascii;
            String caracter;

            ascii = socketIn.readUnsignedShort();
            char asciiToChar = (char) ascii;
            nrmax = socketIn.readUnsignedShort();
            System.out.println("caracterul = " + asciiToChar );
            System.out.println("nr max = " + nrmax);

            reader.close();
            c.close();

        } catch (Exception e) {
            System.err.println("Eroare la conectare server!\n");
        }

    }
}
