#pragma once

#include <string>
#include "model.hpp"

namespace mvc {

/**
 * @brief The Application class
 * A controller for documents
 */
class Controller {
 public:
  /**
   * @brief Creates a new empty document
   * @return Pointer to a created document
   */
  const Document::Ptr& create_document() {
    auto [it, b_inserted] = m_documents.emplace(std::make_unique<Document>());
    assert(b_inserted);
    return *it;
  }

  /**
   * @brief Imports document from a file
   * @return Pointer to the imported document
   */
  const Document::Ptr& import_document(const std::string& filename) {
    auto [it, b_inserted] = m_documents.emplace(Document::load(filename));
    assert(b_inserted);
    return *it;
  }

  /**
   * @brief Exports document to a file
   */
  void export_document(const Document::Ptr& document,
                       const std::string& filename) {
    Document::save(document, filename);
  }

  /**
   * @brief Closes the given document
   * @param[in] document Document to be closed
   * @return `true` if a document existed and was closed, `false` otherwise
   */
  bool close_document(const Document::Ptr& document) {
    std::size_t removed = m_documents.erase(document);
    if (removed == 0)
      return false;
    return true;
  }

 private:
  std::unordered_set<Document::Ptr> m_documents;
};

}  // namespace mvc