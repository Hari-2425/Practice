public class UPIPayment implements PaymentStrategy {
    
    String upiID;

    public UPIPayment(String upiID) {
        this.upiID = upiID;
    }
    public
    @Override
    void Pay(double amount){
        System.out.println("Payment done via UPI");
    }
}
