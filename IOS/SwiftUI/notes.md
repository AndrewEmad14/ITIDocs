# basic boiler plate

    // your view file
    import SwiftUI
    struct UltimateTextField: View {
        var body: some View {
            //your stuff here
        }
    }
    #Preview {
        UltimateTextField()
    }

    //the main that runs your  first view
    import SwiftUI

    @main
    struct SwiftUI_BasicsApp: App {
        var body: some Scene {
            WindowGroup {
                ContentView()
            }
        }
    }

# Binidng <T>

    think of it like a safe pointer that gives your read and write access to the variable

    its null safe , gets automatically deallocated and type safe

    //under the hood look
    struct Binding<Value> {
    let get: () -> Value
    let set: (Value) -> Void

    var wrappedValue: Value {
        get { get() }
        set { set(newValue) }
    }

}

# TextField

    text field must take a binding String data type
    you can give it a binding data type like this
    var x:String
    $x      //binding
