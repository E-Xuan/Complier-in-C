(define (myinterpreter x)
	;(display x) 
	;(newline)
	(mainEval (cadr x) '())
)

(define (mainEval x bindings) 
	;(display x) 
	;(newline)
	;(display bindings)
	;(newline)
	(cond
		;ID cond
		((symbol? x)
			(getValue x bindings)
		)

		;Const Cond
		((integer? x) 	
			x
		)

		;planIf Cond
		((equal? (car x) 'planIf)
			(ifEval (cadr x) (caddr x) (cadddr x) bindings)
		)

	 	;planAdd Cond
		((equal? (car x) 'planAdd)
			(+ (mainEval (cadr x) bindings) (mainEval (caddr x) bindings))
		)

	 	;planMul Cond
	 	((equal? (car x) 'planMul)
			(* (mainEval (cadr x) bindings) (mainEval (caddr x) bindings))
		)

		;planSub Cond
		((equal? (car x) 'planSub)
			(- (mainEval (cadr x) bindings) (mainEval (caddr x) bindings))
		)

		;planLet Cond
		((equal? (car x) 'planLet)
			(letEval (cadr x) (caddr x) (cadddr x) bindings)
		)

		;planFunction cond
		((equal? (car x) 'planFunction)
			x
		)

		;<ID> <expr> Cond
		(else 
			(callEval x bindings)
		)
	)
)

;getID method
(define (getValue id bindings)
	(if (equal? id (caar bindings))
		(cdar bindings)
		(getValue id (cdr bindings))	
	)
)

;ifEval method
(define (ifEval condition exprOne exprTwo bindings)
	(if (> (mainEval condition bindings) 0)
		(mainEval exprOne bindings)
  		(mainEval exprTwo bindings)
	)
)

;letEval method
(define (letEval id exprOne exprTwo bindings)
	(mainEval exprTwo 
		(cons 
			(cons id (mainEval exprOne bindings))
			bindings
		)
	)
)

;callEval method
(define (callEval id bindings)
	(mainEval 
		(caddr (getValue (car id) bindings))
		
		(cons
			(cons 
				(cadr (getValue (car id) bindings))
				(mainEval (cadr id) bindings)
			)
			bindings
		)
	)
)
