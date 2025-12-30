public class CashPayment implements PaymentStrategy {
    
    public CashPayment() {
    }
    @Override
    public void Pay(double amount){
        System.out.println("Payment done via cash");
    }
}
