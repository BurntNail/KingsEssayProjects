use std::{error::Error, fmt::Display, fs::read_to_string};

#[derive(Debug)]
pub enum ArgsParsingFailure {
    MissingEverything,
    MissingPattern
}

impl Display for ArgsParsingFailure {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "{self:?}")
    }
}

impl Error for ArgsParsingFailure {}


#[derive(Debug)]
pub struct ArgsReadingFailure(std::io::Error);

impl From<std::io::Error> for ArgsReadingFailure {
    fn from(value: std::io::Error) -> Self {
        Self(value)
    }
}

impl Display for ArgsReadingFailure {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "{self:?}")
    }
}

impl Error for ArgsReadingFailure {
    fn source(&self) -> Option<&(dyn Error + 'static)> {
        Some(&self.0)
    }
}


#[derive(Debug)]
pub enum ArgsError {
    Parsing(ArgsParsingFailure),
    Reading(ArgsReadingFailure),
}

impl From<ArgsParsingFailure> for ArgsError {
    fn from(value: ArgsParsingFailure) -> Self {
        Self::Parsing(value)
    }
}
impl From<ArgsReadingFailure> for ArgsError {
    fn from(value: ArgsReadingFailure) -> Self {
        Self::Reading(value)
    }
}
impl From<std::io::Error> for ArgsError {
    fn from(value: std::io::Error) -> Self {
        Self::Reading(value.into())
    }
}

impl Display for ArgsError {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "{self:?}")
    }
}

impl Error for ArgsError {
    fn source(&self) -> Option<&(dyn Error + 'static)> {
        match self {
            ArgsError::Parsing(parse) => Some(parse),
            ArgsError::Reading(read) => Some(read),
        }
    }
}


pub struct Args {
    pub file_contents: String,
    pub pattern: String
}

impl TryFrom<Vec<String>> for Args {
    type Error = ArgsError;

    fn try_from(mut value: Vec<String>) -> Result<Self, Self::Error> {
        match value.len() {
            0 => return Err(ArgsParsingFailure::MissingEverything.into()),
            1 => return Err(ArgsParsingFailure::MissingPattern.into()),
            _ => {}
        }

        let file = value.remove(0);
        let pattern = value.remove(0);

        let file_contents = read_to_string(file)?;

        Ok(Args {file_contents, pattern})
    }
}