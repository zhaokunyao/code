import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import java.util.Random;

/**
 * Graph
 *
 * the main.
 *
 * @version 1.0
 */
public class Graph {

    /**
     * main
     *
     * the main function.
     *
     * @access public
     * @param string[]
     */
    public static void main(String[] args) {
        System.out.println("Starting the game ...");

        // create a warehouse as a square (n x n) array of rooms
        Warehouse wareHouse = new Warehouse(8);

        // install doors
        // moved to the constructor
        // wareHouse.install();

        // print
        wareHouse.print();

        // scatter items
        List<Item> itemList = makeItemList();
        wareHouse.installItems(itemList);

        // install hero
        Hero hero = new Hero();
        wareHouse.installHero(hero);

        // start the game
        wareHouse.startGame();
    }

    /**
     * makeItemList
     *
     * @access private
     * @return List<Item>
     */
    private static List<Item> makeItemList() {
        List<Item> itemList = new ArrayList<Item>();
        List<String> itemNamelist = getItemNames();

        Random r = new Random();
        for(String itemName:itemNamelist){
            // make an item
            Item item = new Item();

            //random 5-15
            int size=r.nextInt(11) + 5;
            //random 1-20
            int value=r.nextInt(20) + 1;

            item.setName(itemName);
            item.setSize(size);
            item.setValue(value);

            // add to list
            itemList.add(item);
        }

        return itemList;
    }

    /**
     * get item name from file
     * @access private
     * @return List<String>
     */
    private static List<String> getItemNames(){
        List<String> itemNamelist = new ArrayList<String>();
        File file = new File(Thread.currentThread()
            .getContextClassLoader().getResource("").getPath() + "item_name.txt");
        BufferedReader reader = null;
        try {
            reader = new BufferedReader(new FileReader(file));
            String tempString = null;
            while ((tempString = reader.readLine()) != null) {
                itemNamelist.add(tempString);
            }
            reader.close();
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            if (reader != null) {
                try {
                    reader.close();
                } catch (IOException e1) {
                }
            }
        }
        return itemNamelist;
    }
}
