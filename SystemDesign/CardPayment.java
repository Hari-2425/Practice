public class CardPayment implements PaymentStrategy {

    String cardNumber;

    public CardPayment(String cardNum) {
        this.cardNumber = cardNum;
    }
    
    public
    @Override
    void Pay(double amount){
        System.out.println("Payment done via card");
    }
}
