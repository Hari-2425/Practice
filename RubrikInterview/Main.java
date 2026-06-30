import java.util.*;
import java.util.concurrent.*;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;

class BackupJob {
    private final String id;

    public BackupJob(String id) {
        this.id = id;
    }

    public String getId() {
        return id;
    }

    public void execute() {
        System.out.println(
            Thread.currentThread().getName()
            + " running " + id);
    }
}

class BackupScheduler {

    private final BlockingQueue<BackupJob> queue = new LinkedBlockingQueue<>();

    private final Set<String> runningJobs = ConcurrentHashMap.newKeySet();

    

    public void submit(BackupJob job) {
        queue.offer(job);
    }

    public void start() {

        for(int i=0;i<5;i++) {

            Thread worker = new Thread(() -> {

                while(true) {
                    try {
                        BackupJob job = queue.take();

                        if(!runningJobs.add(job.getId())){
                            continue;
                        }
                        
                        try {
                            job.execute();
                        } finally {
                            runningJobs.remove(job.getId());
                        }
                        
                    } 

                    catch (Exception e) {
                        Thread.currentThread().interrupt();
                    }
                }

            });

            worker.start();
        }
    }
}


class StorageBlock {
    private final int id;

    StorageBlock(int id) {
        this.id = id;
    }

    public int getId() {
        return id;
    }
}


class Job {
    private final String id;

    Job(String id) {
        this.id = id;
    }

    public String getId() {
        return id;
    }

    public void execute() {
        System.out.println(
            Thread.currentThread().getName()
            + " executing " + id);
    }
}

class JobScheduler {

    private final BlockingQueue<Job> queue =
            new LinkedBlockingQueue<>();

    private final Set<String> runningJobs =
            ConcurrentHashMap.newKeySet();

    public void submit(Job job) {
        queue.offer(job);
    }

    public void start() {

        for(int i=0;i<5;i++) {

            new Thread(() -> {

                while(true) {

                    try {

                        Job job = queue.take();

                        if(!runningJobs.add(job.getId())){
                            System.out.println(
                                Thread.currentThread().getName() + " skipped " + job.getId());
                            continue;
                        }


                        try {
                            job.execute();
                        } finally {
                            runningJobs.remove(job.getId());
                        }

                    }
                    catch(Exception e) {
                        e.printStackTrace();
                        break;
                    }
                }

            }).start();
        }
    }
}

class StorageAllocator {
    int cap;
    private final BlockingQueue<StorageBlock> freeBlocks;

    private final Set<Integer> allocatedBlocks = ConcurrentHashMap.newKeySet();

    public StorageAllocator(int n) {
        this.cap = n;
        freeBlocks = new ArrayBlockingQueue<>(cap);
        for(int i=1;i<=n;i++) {
            freeBlocks.add(new StorageBlock(i));
        }
    }

    public StorageBlock allocate() {

        try {
            StorageBlock block = freeBlocks.take();

            boolean isAllocated = allocatedBlocks.add(block.getId());

            if(!isAllocated){
                freeBlocks.put(block);
                throw new IllegalStateException();
            }

            return block;
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
        return null;
    }

    public void release(StorageBlock block) {

        try {
            if(allocatedBlocks.remove(block.getId())){
                freeBlocks.put(block);
            }

            else{
                System.out.println("Block not found!");
            }
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }
}


class StorageNode {

    private final String id;

    public final ReentrantLock lock =
            new ReentrantLock();

    StorageNode(String id) {
        this.id = id;
    }

    public String getId() {
        return id;
    }
}

class FileService {

    public void copy(
            StorageNode source,
            StorageNode destination) {

        StorageNode first = (source.getId().compareTo(
            destination.getId()
        ) < 0)? source : destination;

        StorageNode second = (first==source) ? destination : source;

        first.lock.lock();

        try {

            second.lock.lock();

            try {

                System.out.println(
                        "Copying from "
                        + source.getId()
                        + " to "
                        + destination.getId());

            }
            finally {
                second.lock.unlock();
            }

        }
        finally {
            first.lock.unlock();
        }
    }
}


class TicketService {

    private final ConcurrentHashMap<Integer, String>
            bookedSeats = new ConcurrentHashMap<>();

    public boolean bookSeat(
            int seatId,
            String userId) {

        // if(bookedSeats.containsKey(seatId)) {
        //     return false;
        // }

        // bookedSeats.put(seatId, userId);

        return bookedSeats.putIfAbsent(seatId, userId)==null;
    }
}



class BackupCoordinator {

    private final AtomicBoolean running =
            new AtomicBoolean(false);

    public void runBackup() {

        // if(running.get()) {
        //     return;
        // }

        // running.set(true);

        if(!running.compareAndSet(false, true)){
            return;
        }

        try {

            System.out.println(
                Thread.currentThread().getName()
                + " running backup");

            Thread.sleep(1000);

        }
        catch(Exception e) {
            e.printStackTrace();
        }
        finally {
            running.set(false);
        }
    }
}

class MetricsCollector {

    private final ConcurrentHashMap<String, AtomicInteger>
            counters = new ConcurrentHashMap<>();

    public void increment(String key) {

        counters.computeIfAbsent(key, k->new AtomicInteger(0)).incrementAndGet();
    }

    public AtomicInteger getCount(String key) {
        return counters.getOrDefault(key, new AtomicInteger(0));
    }
}

class JobQueue{
    int cap;
    private final Queue<Job> queue;
    private final ReentrantLock lock;
    Condition notFull;
    Condition notEmpty;

    public JobQueue(int cap) {
        this.cap = cap;
        queue = new ArrayDeque<>(cap);
        lock = new ReentrantLock();
        notFull = lock.newCondition();
        notEmpty = lock.newCondition();
    }
    
    public void producer(Job jb){
        lock.lock();
        try {
            while(queue.size()>=cap){
                notFull.await();
            }
            queue.add(jb);
            notEmpty.signal();
        }
        catch(InterruptedException e){
            Thread.currentThread().interrupt();
        }
        finally {
            lock.unlock();
        }
    }

    public void consumer(){
        lock.lock();
        try {
            while(queue.isEmpty()){
                notEmpty.await();
            }
            queue.poll();
            notFull.signal();
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        } finally {
            lock.unlock();
        }
    }
}


class TaskProcessor {

    private final Queue<Integer> queue = new LinkedList<>();

    private final ReentrantLock lock = new ReentrantLock();

    private final Condition notEmpty =
            lock.newCondition();

    private boolean shutdown = false;

    private int processed = 0;

    public void submit(int task) {

        lock.lock();

        try {
            queue.offer(task);

            if (queue.size() == 1) {
                notEmpty.signal();
            }

        } finally {
            lock.unlock();
        }
    }

    public void stop() {

        shutdown = true;

        lock.lock();

        try {
            notEmpty.signal(); // It should be signalAll
        } finally {
            lock.unlock();
        }
    }

    class Worker extends Thread {

        public void run() {

            while (true) {

                Integer task = null;

                lock.lock();

                try {

                    if (queue.isEmpty() && !shutdown) { // while should be used
                        notEmpty.await();
                    }

                    if (shutdown) { // here (queue.isEmpty() && shutdown)
                        break;
                    }

                    if (!queue.isEmpty()) {
                        task = queue.poll();
                    }

                } catch (InterruptedException e) {

                    return;// Ignored/Swallowed interruption
                } finally {
                    lock.unlock();
                }

                if (task != null) {

                    processed++; // Not atomic

                    System.out.println(
                        "Processed " + task);
                }
            }
        }
    }
}

class TaskQueue {

    private final Queue<Integer> queue =
            new LinkedList<>();

    private final ReentrantLock lock =
            new ReentrantLock();

    private final Condition notEmpty =
            lock.newCondition();

    private volatile boolean shutdown =
            false;

    private int processed = 0;

    public void submit(int task) {

        lock.lock();

        try {

            queue.offer(task);

            notEmpty.signal();

        } finally {
            lock.unlock();
        }
    }

    public void shutdown() {

        shutdown = true;

        lock.lock();

        try {
            notEmpty.signalAll();
        } finally {
            lock.unlock();
        }
    }

    class Worker extends Thread {

        @Override
        public void run() {

            while (true) {

                Integer task = null;

                lock.lock();

                try {

                    while (queue.isEmpty()) {

                        if (shutdown) {
                            return;
                        }

                        notEmpty.await();
                    }

                    task = queue.poll();

                } catch (InterruptedException e) {
                    return; //swallowed exception/Not interrupted
                } finally {
                    lock.unlock();
                }

                process(task); // No catch block to catch exception

                processed++; // Not atomic
            }
        }

        private void process(Integer task) { // task should be an atomic integer

            if (task % 37 == 0) { // because of this we cannot see 100 task processed ever.
                throw new RuntimeException(
                        "processing failed");
            }
        }
    }
}

class ResourceManager {

    private final Object chair = new Object();
    private final Object scissor = new Object();

    public void haircut() {

        synchronized (chair) { // <- Deadlock

            sleep(10);

            synchronized (scissor) { // <- Deadlock

                sleep(10);

                cutHair();
            }
        }
    }

    public void cleanTools() {

        synchronized (scissor) { // <- Deadlock

            sleep(10);

            synchronized (chair) { // <- Deadlock

                sleep(10);

                sanitize();
            }
        }
    }

    private void cutHair() {}

    private void sanitize() {}

    private void sleep(long ms) {
        try {
            Thread.sleep(ms);
        } catch (InterruptedException e) {
            // Ignored interrupt
        }
    }
}


class JobSystem {

    private final Queue<Integer> queue =
            new LinkedList<>();

    private final ReentrantLock lock =
            new ReentrantLock();

    private final Condition notEmpty =
            lock.newCondition();

    private volatile boolean shutdown =
            false;

    private int processed = 0; // Need to be atomic

    public void submit(int job) { // Submit is independent, does not have visibility to shutdown

        lock.lock();

        try {

            queue.offer(job);

            notEmpty.signal();

        } finally {
            lock.unlock();
        }
    }

    public void shutdown() {

        shutdown = true; // No signallAll to the worker threads
        // Most Subtle Bug - Not sharing same lock with consumer, and because of that
        // consumer could miss the shutdown=true state transition
    }

    class Consumer extends Thread {

        @Override
        public void run() {

            while (true) {

                Integer job = null;

                lock.lock();

                try {

                    while (queue.isEmpty()) {

                        if (shutdown) {
                            return;
                        }

                        notEmpty.await();
                    }

                    job = queue.poll();

                } catch (InterruptedException e) {
                    // No interrupt
                    return;
                } finally {
                    lock.unlock();
                }

                process(job); // No caught exception

                processed++; // Not atomic
            }
        }

        private void process(Integer job) {
            // process job
        }
    }
}

class BarberShop {

    private final Semaphore chairs =
            new Semaphore(3);

    private final Semaphore scissors =
            new Semaphore(1);

    public void serveCustomer() throws Exception {

        chairs.acquire();

        scissors.acquire();

        if (ThreadLocalRandom.current()
                .nextInt(100) < 5) {
            throw new RuntimeException(
                    "customer left");
        } // because of this ccustomer left policy, exception will be thrown
        // scissors release won't be happening and since scissors permit is 1
        // the other 2 threads wait forever.

        cutHair();

        scissors.release();

        chairs.release();
    }

    private void cutHair() {
    }
}


class TaskExecutor {

    private final Queue<Runnable> queue =
            new LinkedList<>();

    private final ReentrantLock lock =
            new ReentrantLock();

    private final Condition notEmpty =
            lock.newCondition();

    private boolean shutdown = false;

    public void submit(Runnable task) { // No coordination with shutdown

        lock.lock();

        try {

            queue.offer(task);

            notEmpty.signal();

        } finally {
            lock.unlock();
        }
    }

    public void shutdown() {

        lock.lock();

        try {
            shutdown = true; // Did not signalAll to worker threads
        } finally {
            lock.unlock();
        }
    }

    class Worker extends Thread {

        @Override
        public void run() {

            while (true) {

                Runnable task = null;

                lock.lock();

                try {

                    while (queue.isEmpty() && !shutdown) {
                        notEmpty.await();
                    }

                    if (queue.isEmpty() && shutdown) {
                        return;
                    }

                    task = queue.poll();

                } catch (InterruptedException e) {
                    return;// Ignored interrupt
                } finally {
                    lock.unlock();
                }

                task.run();
            }
        }
    }
}


class BarberShop2 {

    private final Semaphore chairs =
            new Semaphore(3);

    private final Semaphore scissors =
            new Semaphore(1);

    private final ReentrantLock lock =
            new ReentrantLock();

    private final Condition customerAvailable =
            lock.newCondition();

    private int waitingCustomers = 0;

    private boolean shutdown = false;

    public void enterShop() throws Exception {

        chairs.acquire();

        lock.lock();

        try {

            waitingCustomers++;

            customerAvailable.signal();

        } finally {
            lock.unlock();
        }

        getHaircut();

        chairs.release();
    }

    private void getHaircut() throws Exception {

        scissors.acquire();

        try {

            Thread.sleep(50); // unnecessary sleep

        } finally {

            scissors.release();
        }
    }

    public void barber() throws Exception {

        while (true) {

            lock.lock();

            try {

                while (waitingCustomers == 0
                        && !shutdown) {

                    customerAvailable.await(); // Only 1 or 2 workers will be signaled
                    // when shutdown is called. So other workers will wait forever.
                }

                if (shutdown) {
                    return; // even if waitingCustomers>0, workers still exit. 
                    // Could be a reason not to show 30 processed
                }

                waitingCustomers--;

            } finally {
                lock.unlock();
            }

            Thread.sleep(10); // unnecessary sleep
        }
    }

    public void shutdown() {

        lock.lock();

        try {

            shutdown = true;

            customerAvailable.signal(); // no signalAll

        } finally {
            lock.unlock();
        }
    }
}

public class Main {

    public static void main(String[] args) {

        BackupCoordinator c =
                new BackupCoordinator();

        Runnable r = c::runBackup;

        new Thread(r).start();
        new Thread(r).start();
    }
}