package com.jackmaguire;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Main {
    public static void main(String[] args) {
        switch (args.length) {
            case 0 -> {
                System.err.println("You need to pass in a file as the first argument.");
                return;
            }
            case 1 -> {
                System.err.println("You need to pass in a pattern to look for as the second argument.");
                return;
            }
        }


        List<String> lines = new ArrayList<>();
        try {
            BufferedReader reader = new BufferedReader(new FileReader(args[0]));
            String line;
            while ((line = reader.readLine()) != null) {
                lines.add(line);
            }
            reader.close();

        } catch (FileNotFoundException ex)
        {
            System.err.println("File not found: " + ex.getMessage());
            return;
        }
        catch (IOException ex) {
            System.err.println("Error reading from file: " + ex.getMessage());
            return;
        }

        Pattern pattern = Pattern.compile(args[1], Pattern.CASE_INSENSITIVE);
        ExpandableBitVec ebv = new ExpandableBitVec(256);
        for (String line : lines) {
            Matcher matcher = pattern.matcher(line);
            if (matcher.find()) {
                do {
                    for (int i = matcher.start(); i < matcher.end(); i++) {
                        ebv.set(i);
                    }
                } while (matcher.find(matcher.start()+1));
            }

            int col = 0;
            for(char c : line.toCharArray())
            {
                if (ebv.index(col))
                {
                    System.out.print("\u001B[32m" + c + "\u001B[37m");
                } else {
                    System.out.print(c);
                }
                col++;
            }

            System.out.println("");
            ebv.clear();
        }
    }
}