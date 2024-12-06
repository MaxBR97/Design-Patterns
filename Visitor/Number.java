
class Number implements  Type {
    int value;
    public Number(int x){
        value = x;
    }

    @Override
    public Type accept(Visitor v, int extraParam) {
        return v.visit(this, extraParam);
    }

    public String toString(){
        return new Integer(value).toString();
    }
}