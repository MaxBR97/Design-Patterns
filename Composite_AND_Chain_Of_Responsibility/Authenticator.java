
class Authenticator extends Handler {

    public <T extends Handler> Authenticator( T handler){
        this.nextHandler = handler;
    }

    @Override
    public <T> void process(T request) {
        if(request instanceof String) {
            System.out.println("Authenticated");
        }
    }

    
}    