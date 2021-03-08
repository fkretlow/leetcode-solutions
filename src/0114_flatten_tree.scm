(define (make-tree val left right) (list val left right))
(define tree-left cadr)
(define tree-right caddr)
(define tree-value car)

(define (flatten-tree tree)
  (define (iter node acc)
    (if (null? node)
        acc
        (cons tree-value
              (iter (tree-left node) (iter (tree-right node acc))))))
  (iter tree '()))
