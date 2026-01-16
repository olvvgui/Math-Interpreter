function Calculator() {
  const buttons = [
    "7",
    "8",
    "9",
    "C",
    "+",
    "-",
    "4",
    "5",
    "6",
    "0",
    "x",
    "/",
    "1",
    "2",
    "3",
    ".",
    "^",
    "=",
  ];
  return (
    <div className="calculator-container">
      <div className="calculator">
        <div className="text-container">hello</div>
        <div className="keypad-container">
          {buttons.map((label) => (
            <button key={label}>{label}</button>
          ))}
        </div>
      </div>
    </div>
  );
}

export default Calculator;
