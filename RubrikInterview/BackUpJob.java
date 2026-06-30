
import java.util.*;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantReadWriteLock;

public class BackUpJob {
    String jobId;
    int createTime;

    public BackUpJob(String id, int ct) {
        this.jobId = id;
        this.createTime = ct;
    }
    
}

class Solution{
    PriorityQueue<BackUpJob> pq = new PriorityQueue<>((a, b)->Integer.compare(a.createTime, b.createTime));
    Set<String> cancelledJobs = new HashSet<>();
    private final ReentrantReadWriteLock lock = new ReentrantReadWriteLock();
    private final Lock writeLock = lock.writeLock();
    private final Lock readLock = lock.readLock();

    public void addJob(String id, int ct){
        

        writeLock.lock();
        try {
            pq.add(new BackUpJob(id, ct));
        } 
        finally{
            writeLock.unlock();
        }
    }

    public BackUpJob getNextJob(){
        

        writeLock.lock();
        try {
            while(!pq.isEmpty() && cancelledJobs.contains(pq.peek().jobId)){
                pq.poll();
            }
            return pq.peek();
        } 
        finally{
            writeLock.unlock();
        }
    }

    public void cancelJob(String id){
        writeLock.lock();
        try {
            cancelledJobs.add(id);
        } finally {
            writeLock.unlock();
        }
    }

    public List<String> executeDueJobs(int currTime){
        List<String> res = new ArrayList<>();
        
        writeLock.lock();
        try {
            BackUpJob next = getNextJob();
            while(!pq.isEmpty() && next!=null && next.createTime <= currTime){
                ExecuteJob(next);
                res.add(pq.poll().jobId);
            }

            return res;
        } finally {
            writeLock.unlock();
        }
    }

    public void ExecuteJob(BackUpJob jb){
        System.out.println("Executing job - " + jb.jobId);
    }
}
