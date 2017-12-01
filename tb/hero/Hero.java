import java.util.Collections;
import java.util.Comparator;
import java.util.LinkedList;
import java.util.List;

public class Hero {

    /**
     * backpack
     */
    private List<Item> itemList=new LinkedList<Item>();

    public List<Item> getItemList() {
        return itemList;
    }

    /**
     * pick up one fo item
     * @param itemIndex
     */
    public boolean pickUp(Item item){
        int itemSize = this.getSumItemSize();

        //backpack of capacity 50.
        if(itemSize + item.getSize() > 50){
            return false;
        }

        this.itemList.add(item);

        // sort by size asc
        this.itemListSort();
        return true;
    }

    /**
     * sort by item's size
     */
    private void itemListSort(){
        Collections.sort(itemList, new Comparator<Item>() {
            public int compare(Item o1, Item o2) {
                if(o1.getSize()>o2.getSize()){
                    return 1;
                }else if(o1.getSize()==o2.getSize()){
                    return 0;
                }else{
                    return -1;
                }
            }
        });
    }

    /**
     * drop one of item
     * @param itemIndex
     */
    public void drop(Item item){
        this.itemList.remove(item);
    }

    /**
     * 获取size之和
     * @return
     */
    private int getSumItemSize(){
        int size=0;
        if(itemList!=null && itemList.size()>0){
            for(Item item:itemList){
                size+=item.getSize();
            }
        }
        return size;
    }
}
