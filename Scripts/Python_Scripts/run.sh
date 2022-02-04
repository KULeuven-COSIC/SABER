# clone the estimator and setup in framework folder
git clone https://github.com/lducas/leaky-LWE-Estimator.git tmp
cp -r tmp/framework framework

# run the script
cd select_params
sage select_params.py