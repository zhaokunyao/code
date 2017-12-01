

public class Item {

    private String name;
    private int size;
    private int value;
    public String getName() {
        return name;
    }
    public void setName(String name) {
        this.name = name;
    }
    public int getSize() {
        return size;
    }
    public void setSize(int size) {
        this.size = size;
    }
    public int getValue() {
        return value;
    }
    public void setValue(int value) {
        this.value = value;
    }
    @Override
    public String toString() {
        return "Item [name=" + name + ", size=" + size + ", value=" + value + "]";
    }

    public String print(){
        return name+" (size "+size+", value "+value+")";
    }
}
