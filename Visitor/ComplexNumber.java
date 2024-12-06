

class ComplexNumber implements Type {
    float real;
    float imaginary;
    public ComplexNumber(float r, float i){
        real = r;
        imaginary = i;
    }

    @Override
    public Type accept(Visitor v, int extraParam) {
        return v.visit(this, extraParam);
    }

    public String toString(){
        return new Float(real).toString() +" "+ new Float(imaginary).toString();
    }
}