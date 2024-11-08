
class Authorizer extends Handler {

    public <T extends Handler> Authorizer(T handler){
        this.nextHandler = handler;
    }

    public <T> void process(T request) {
        if (request instanceof String) {
            System.out.println("Authorizing");
        }
    }
}