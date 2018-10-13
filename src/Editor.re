open BsReactNative;

type state = {
  saved: bool,
  text: string,
};

type action =
  | ChangeText(string);

let component = ReasonReact.reducerComponent("Editor");

let make = (~autoFocus=?, _children) => {
  ...component,
  initialState: () => {saved: false, text: "Write a note here!"},
  reducer: (action, state) =>
    switch (action) {
    | ChangeText(text) => ReasonReact.Update({...state, text})
    },
  render: self =>
    <View>
      <TextInput
        ?autoFocus
        multiline=true
        onChangeText={text => self.send(ChangeText(text))}
        underlineColorAndroid="transparent"
        value={self.state.text}
      />
    </View>,
};
