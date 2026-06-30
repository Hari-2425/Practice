import java.util.HashMap;
import java.util.concurrent.locks.ReentrantLock;

class Node{
    int key;
    int val;

    Node prev;
    Node next;

    public Node(int key, int val) {
        this.key = key;
        this.val = val;
        prev = next = null;
    }

    
}

public class lruCache {
    Node headNode;
    Node tailNode;
    int cap;
    int count;
    public HashMap<Integer, Node> cacheMap = new HashMap<>();

    private ReentrantLock lock = new ReentrantLock();

    public lruCache(int cap) {
        this.cap = cap;
        this.count = 0;
    }


    public void remove_node(Node node){
        // removal of node
        node.prev.next = node.next;
        node.next.prev = node.prev;
    }

    public void add_to_front(Node node){
        // add to front
        node.next = headNode.next;
        headNode.next.prev = node;
        headNode.next = node;
        node.prev = headNode;
    }

    public int get(int key){
        lock.lock();
        try {
            if(!cacheMap.containsKey(key)){
                return -1;
            }
            remove_node(cacheMap.get(key));
            add_to_front(cacheMap.get(key));
            return cacheMap.get(key).val;
        } finally {
            lock.unlock();
        }
    }

    public void put(int key, int val){
        lock.lock();
            try {
                if(cacheMap.containsKey(key)){
                cacheMap.replace(key, new Node(key, val));
                remove_node(cacheMap.get(key));
                add_to_front(cacheMap.get(key));
            }
            else{
                if(count >= cap){
                    // evict lru node
                    tailNode.prev = tailNode.prev.prev;
                    tailNode.prev.next = tailNode;
                }
                Node newNode = new Node(key, val);
                add_to_front(newNode);
                cacheMap.put(key, newNode);
            }
        } finally {
            lock.unlock();
        }
    }

    
    public static void main(String[] args) {
        
    }
}
