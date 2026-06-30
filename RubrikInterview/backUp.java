

import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;

class Job{
    private final char jobId;
    private final int createTime;
    private final int endTime;
    private final int retainTime;
    Job parent;

    Job(char id, int ct, int et, int rt){
        this.jobId = id;
        this.createTime = ct;
        this.endTime = et;
        this.retainTime = rt;
        parent = null;
    }

    public int getEndTime(){
        return this.endTime;
    }

    public int getRetainTime(){
        return this.retainTime;
    }

    public char getJobId(){
        return this.jobId;
    }

}

public class backUp {

    public static HashMap<Character, List<Job>> dep = new HashMap<>();
    // A -> B

    public static HashMap<Character, List<Job>> revDep = new HashMap<>();

    public static void add_dependency(Job a, Job b){
        dep.putIfAbsent(a.getJobId(), new ArrayList<>());
        dep.get(a.getJobId()).add(b);

        revDep.putIfAbsent(b.getJobId(), new ArrayList<>());
        revDep.get(b.getJobId()).add(a);
    }

    public static void find_recovery_chain_dfs(char node, HashSet<Character> uniqueIds,
        List<Character> res, int pit)
    {
        uniqueIds.add(node);
        res.add(node);
        boolean fl = false;
        
        
        for(Job jb: revDep.get(node)){
            
            if(!uniqueIds.contains(jb.getJobId()) && 
            jb.getEndTime()+jb.getRetainTime()>=pit){
                fl = true;
                find_recovery_chain_dfs(jb.getJobId(), uniqueIds, res, pit);
            }
        }
        if(!fl){
            for(char jb: res){
                System.out.print(jb+"->");
            }
            System.out.println("\n");
        }
        res.remove(res.size()-1);
    }

    public static void find_recovery_chain(char backUpId, int pit){
        
        HashSet<Character> uniqueIds = new HashSet<>();
        List<Character> res = new ArrayList<>();

        find_recovery_chain_dfs(backUpId, uniqueIds, res, pit);
    }

    public static void main(String[] args) {
        Integer now = 0;
        
        Job j1 = new Job('A',0 , 0, 10);
        Job j2 = new Job('B',1 , now+1, 3);
        Job j3 = new Job('C',0 , now+2, 4);
        Job j4 = new Job('D',0 , now+3, 7);
        Job j5 = new Job('E',0 , now+4, 5);
        Job j6 = new Job('F',0 , now+5, 12);
        
        add_dependency(j1, j2);
        add_dependency(j2, j3);
        add_dependency(j3, j4);
        add_dependency(j4, j5);
        add_dependency(j5, j6);

        find_recovery_chain('F', 6);
        
    }
}
