

public class Chasing_pavements {

    public static void main(String[] args) {
        String lyrics = "Should I give up?\n" +
                        "Or should I just keep chasing pavements?\n" +
                        "Even if it leads nowhere\n" +
                        "Or would it be a waste?\n" +
                        "Even if I knew my place, should I leave it there?\n" +
                        "Should I give up?\n" +
                        "Or should I just keep chasing pavements?\n" +
                        "even if it leads nowhere";

        int defaultWordDelay = 150; // milliseconds

        String[] lines = lyrics.split("\n");

        for (String line : lines) {
            String[] words = line.split(" ");

            for (String word : words) {
                System.out.print(word + " ");
                try {
                    String cleanedWordForLookup = word.replaceAll("[?!.,]", "");
                    int currentDelay;

                    switch (cleanedWordForLookup) {
                        case "Should":
                            currentDelay = 500;
                            break;
                        case "I":
                            currentDelay = 200; 
                            break;
                        case "give":
                            currentDelay = 600;
                            break;
                        case "up":
                            currentDelay = 900;
                            break;
                        case "Or":
                            currentDelay = 250;
                            break;
                        case "should":
                            currentDelay = 300; 
                            break;
                        case "i": 
                            currentDelay = 800;
                            break;
                        case "just":
                            currentDelay = 400;
                            break;
                        case "keep":
                            currentDelay = 500;
                            break;
                        case "chasing":
                            currentDelay = 500;
                            break;
                        case "pavements":
                            currentDelay = 1300;
                            break;
                        case "Even":
                            currentDelay = 800; 
                            break;
                        case "if":
                            currentDelay = 200;
                            break;
                        case "it":
                            currentDelay = 300;
                            break;
                        case "leads":
                            currentDelay = 900;
                            break;
                        case "nowhere":
                            currentDelay = 2100;
                            break;
                        case "would":
                            currentDelay = 700;
                            break;
                        case "be":
                            currentDelay = 300;
                            break;
                        case "a":
                            currentDelay = 300;
                            break;
                        case "waste":
                            currentDelay = 700;
                            break;
                        case "If":
                            currentDelay = 200; 
                            break;
                        case "knew":
                            currentDelay = 250;
                            break;
                        case "my":
                            currentDelay = 150;
                            break;
                        case "place":
                            currentDelay = 1200;
                            break;
                        case "leave":
                            currentDelay = 280;
                            break;
                        case "there":
                            currentDelay = 2200;
                            break;
                        case "even":
                            currentDelay = 2700
                            ;
                            break;
                        default:
                            currentDelay = defaultWordDelay;
                            break;
                    }

                    Thread.sleep(currentDelay);
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                    System.err.println("Printing interrupted: " + e.getMessage());
                }
            }
            System.out.println();
        }
    }
}