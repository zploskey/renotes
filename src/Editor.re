open BsReactNative;

let component = ReasonReact.statelessComponent("Editor");

let make =
    (~note: Note.t, ~onBack, ~onNoteChanged, ~autoFocus=true, _children) => {
  ...component,
  render: _self =>
    <View>
      <Button title="Back" onPress=onBack> {ReasonReact.string("Back")} </Button>
      <TextInput
        onChangeText={title => onNoteChanged({...note, title})}
        placeholder="Title"
        value={note.title}
      />
      <TextInput
        autoFocus
        multiline=true
        onChangeText={text => onNoteChanged({...note, text})}
        underlineColorAndroid="transparent"
        placeholder="Write your note here"
        value={note.text}
      />
    </View>,
};
