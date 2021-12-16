namespace Auxiliary

module Syntactic =
    
    type private Token =
        | Value of string
        | Id of string
        | Brackets of string
        | Block of string
        | String of string
        | Keyword of string
        | Type of string
        | Operation of string
        | Grammar of string
        | Endline
        | Empty

    let public check (tokensRaw : ResizeArray<int * string>) : bool =
        let tokens = [
            for token in Seq.toList tokensRaw do
                let token = 
                    match token with
                        | (0, x) -> Token.Value(x)
                        | (1, x) -> Token.Id(x)
                        | (2, x) -> Token.Brackets(x)
                        | (3, x) -> Token.Block(x)
                        | (4, x) -> Token.Empty
                        | (5, x) -> Token.String(x)
                        | (6, x) -> Token.Keyword(x)
                        | (7, x) -> Token.Type(x)
                        | (8, x) -> Token.Operation(x)
                        | (9, x) -> Token.Grammar(x)
                        | (10, x) -> Token.Endline
                        | _ -> Token.Empty
                if token <> Token.Empty then yield token
        ]
        for x in tokens do
            printfn $"{x}"
        (false)
