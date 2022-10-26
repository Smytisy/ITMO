
class expression_invalid_range : public std::exception {
    const char *msg;
public:
    expression_invalid_range() : msg("Invalid range") {}

};