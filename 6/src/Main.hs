import           Graphics.Gloss

window :: Display
window = InWindow "Window" (200, 200) (10, 10)

background :: Color
background = white

kochSnowflake :: (Eq a, Num a) => a -> Float -> Picture
kochSnowflake n l =
  pictures
    [ rotate 0 (translate 0 (-sqrt 3 * l / 6) (kochLine l n))
    , rotate 120 (translate 0 (-sqrt 3 * l / 6) (kochLine l n))
    , rotate 240 (translate 0 (-sqrt 3 * l / 6) (kochLine l n))
    ]

kochLine :: (Eq a, Num a) => Float -> a -> Picture
kochLine k 0 = line [(-k / 2, 0), (k / 2, 0)]
kochLine k n =
  pictures
    [ translate (k / 3) 0 (kochLine (k / 3) (n - 1))
    , translate (-k / 3) 0 (kochLine (k / 3) (n - 1))
    , translate
        (-k / 12)
        (-sqrt 3 * k / 12)
        (rotate 60 (kochLine (k / 3) (n - 1)))
    , translate
        (k / 12)
        (-sqrt 3 * k / 12)
        (rotate 300 (kochLine (k / 3) (n - 1)))
    ]

main :: IO ()
main = do
  putStrLn "Enter number of iterations"
  num <- getLine
  putStrLn "Enter length of line"
  len <- getLine
  if null num
    then return ()
    else do
      let n = read num :: Int
          l = read len :: Float
      display window background (kochSnowflake n l)
