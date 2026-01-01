# SWIFT NOTES

    you must type with equal spacing between right and left hand side
    x =5                    X WRONG COMPILER ERROR

    x = 5                   CORRECT

# variables

    you use (var) for a variable
    you use (let) for a constant

    A constant or variable must have the same type as the value you want to assign to it
    However there is type infrence

    var x = 5

    var y = "string"

    if you want to explicitly specify the type you do it like this

    var:Int = 5

    if you try to input

# Datatype

    swift is also a strongly typed language
    if you want to cast you can do it like this

    var:int x
    x = Int(10.5)
    remeber that casting  int or double to string returns optional

    operation wont work without casting too
    let x = 5
    let y = 5.5
    let z = x + y

    conditinal statements only accept bool values which are true and false only

    swift does not have primitve types , instead each data type is in a struct

## Tuples

    let http404Error = (404, "Not Found")
    // http404Error is of type (Int, String), and equals (404, "Not Found")
    var (status,error) = (0,"smol error")
    var https = (0,"https")
    var httpsDescriptive = (mySatuts:0,myError:"https")
    print(status)
    print(error)
    print(https)
    print(httpsDescriptive.mySatuts)

# String

    if you want to include a variable in a string
    var label = 5.5
    let mystr = "Hello\(label)"

# type alias

    Type Aliases

    Type aliases define an alternative name for an existing type. You define type aliases with the typealias keyword.

    Type aliases are useful when you want to refer to an existing type by a name that’s contextually more appropriate, for example working with data of a specific size from an external source:

    typealias AudioSample = UInt16

    Once you define a type alias, you can use the alias anywhere you might use the original name:

    var maxAmplitudeFound = AudioSample.min

# Optional

    You use optionals in situations where a value may be absent. An optional represents two possibilities: Either there is a value of a specified type, and you can unwrap the optional to access that value, or there isn’t a value at all

    var x:Int?
    x = 5
    if(x != nil){                       //brackets are optional
        print("x is not nil")
    }
    You can’t accidentally treat an optional as if it were non-optional because this mistake produces an error at compile time

    var x : Int?
    print( x ?? 5 )                 //fall back value
    print( x! )                     //force unwrapping

    implicitly unwraped optionals //when you are sure the optional is going to have value
    var x : Int!
    x=4;

# Optional Binding

    if let <#constantName#> = <#someOptional#> {
        <#statements#>
    }

    if let actualNumber = Int(possibleNumber) {
    print("The string \"\(possibleNumber)\" has an integer value of \(actualNumber)")
    } else {
        print("The string \"\(possibleNumber)\" couldn't be converted to an integer")
    }

    if let firstNumber = Int("4"), let secondNumber = Int("42"), firstNumber < secondNumber && secondNumber < 100 {
    print("\(firstNumber) < \(secondNumber) < 100")
    }

# Error Handeling

    func canThrowAnError() throws {
        // this function may or may not throw an error
    }

    do {
        try canThrowAnError()
        // no error was thrown
    } catch {
        // an error was thrown
    }

# Computed property

    stored property
    struct MyStruct{
        var x : Int         //a stored property is a constant or variable that’s stored
                            as part of an instance of a particular class or structure.
        lazy var = func()    //A lazy stored property is a property whose initial value
                            isn’t calculated until the first time it’s used

        var center: Point {     //computed property
            get {
                let centerX = origin.x + (size.width / 2)
                let centerY = origin.y + (size.height / 2)
                return Point(x: centerX, y: centerY)
            }
            /*
                get{                            //short hand for git , it return point
                    Point( Point(x: origin.x + (size.width / 2),
                  y: origin.y + (size.height / 2)))
                }

            */
            set(newCenter) {
                origin.x = newCenter.x - (size.width / 2)
                origin.y = newCenter.y - (size.height / 2)
            }
            /* set {           // a short hand for set if no var is declared it is newValue
                    origin.x = newValue.x
                }
            */
        }
        //read only computed properties

        struct Cuboid {
        var width = 0.0, height = 0.0, depth = 0.0
        var volume: Double {
            return width * height * depth
        }

    }
