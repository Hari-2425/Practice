import java.util.concurrent.atomic.AtomicInteger;

public class Counter{
    private final AtomicInteger count = new AtomicInteger(0);

    public void increament(){
        count.incrementAndGet();
    }

    public int get(){
        return count.get();
    }

}