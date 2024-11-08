
class Parser extends Handler {

    public <T extends Handler> Parser( T handler){
        this.nextHandler = handler;
    }

    public <T> void process(T request){
        if(request instanceof String) {
            System.out.println("Parsing");
        }
    }
}