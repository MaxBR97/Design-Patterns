
class Main {
    public static void main(String[] args) {
        Chain_Of_Responsibility requestProcessor = new Authenticator(new Authorizer(new Parser(new Executor())));
        String someMessage = "My Message!";
        requestProcessor.propagate(someMessage);
    }
}